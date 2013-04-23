#include "RenderManager.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <list>
#include <map>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <SDL/SDL_ttf.h>
#include "Ship.h"
#include <memory>
using namespace std;

RenderManager::RenderManager() :
    close_requested(false),
    WINDOW_WIDTH(640), 
    WINDOW_HEIGHT(360), 
    WINDOW_TITLE("Embedded Scripting Woot! C++"),
    _workingShipIdx(0)
{

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(WINDOW_TITLE, 0);
    SDL_Surface* temp = IMG_Load("imgs/Space.png");
    if(temp == 0){
        stringstream s;
        s << "Could not load image: " << IMG_GetError();
        throw runtime_error(s.str());
    }
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    font = TTF_OpenFont("fonts/DejaVuSans.ttf", 12);
    if(font == 0)
    {
        stringstream s;
        s << "Could not initialize Font: " << TTF_GetError();
        throw runtime_error(s.str());

    }
    
    _pallet["green"] = {65, 233, 83};
    _pallet["purple"] = {131, 65, 233};
    _pallet["blue"] = {65, 166, 233};

    SDL_Rect text_location = {475, 20, 0, static_cast<Uint16>(WINDOW_HEIGHT)};
    _eventWindow = make_shared<TextBox>(TextBox(text_location, font));
    _eventWindow->AddMessage("Loading World...", _pallet["green"]);

    SDL_Rect frame_location = {20, 20,  0, static_cast<Uint16>(TTF_FontLineSkip(font))};
    _frameWindow = make_shared<TextBox>(TextBox(frame_location, font));

    for(int i = 0; i < 5; ++i) 
        _worldShips.push_back(make_shared<Ship>(Ship()));

    selectShip(_workingShipIdx);
}

RenderManager::~RenderManager()
{
    TTF_Quit();
    SDL_Quit();
}

bool RenderManager::render_frame()
{
    /* Render Cell here */
    
    fps.Ping();

    SDL_BlitSurface(background, NULL, screen, NULL);
    stringstream ss;
    ss << fps.GetFPS() << " fps";
    _frameWindow->AddMessage(ss.str().c_str(), _pallet["purple"]);

    _eventWindow->Render(screen);
    _frameWindow->Render(screen);

    for( auto ship: _worldShips)
    {
        ship->UpdatePosition();
        ship->Render(screen);
    }

    SDL_Flip(screen);
    const int FRAME_TIME = 41;
    
    while(FRAME_TIME > (SDL_GetTicks() - fps.GetLastFrameTime()))
    {
	    if(SDL_PollEvent(&event))
	    {
		    if(event.type == SDL_QUIT)
		    {
			    close_requested = true;
                SDL_Quit();
                return close_requested;
            }
        }

    }
    
    return close_requested;

}

void RenderManager::unSelectShip(int shipNumber)
{
    stringstream s;
    s << "Unselecting Ship" << _workingShipIdx;
    _eventWindow->AddMessage(s.str().c_str(), _pallet["green"]);
    _worldShips[_workingShipIdx]->UnSelect();
}

void RenderManager::selectShip(int shipNumber)
{
    _worldShips[_workingShipIdx]->UnSelect();
    _workingShipIdx = shipNumber;
    stringstream s;
    s << "Selecting Ship" << shipNumber;
    _eventWindow->AddMessage(s.str().c_str(), _pallet["blue"]);
    _worldShips[shipNumber]->Select();
}

void RenderManager::acclShip(int speed)
{
    _worldShips[_workingShipIdx]->Accl(speed);
}

void RenderManager::turnShip(char c)
{
    switch(c)
    {
        case 'w':
            _worldShips[_workingShipIdx]->Turn(Ship::NORTH);
            break;
        case 'a':
            _worldShips[_workingShipIdx]->Turn(Ship::WEST);
            break;
        case 'd':
            _worldShips[_workingShipIdx]->Turn(Ship::EAST);
            break;
        case 's':
            _worldShips[_workingShipIdx]->Turn(Ship::SOUTH);
            break;
    }
}
