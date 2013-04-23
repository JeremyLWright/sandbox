#include "Ship.h"
#include "RenderUtility.h"
#include "SDL/SDL_rotozoom.h"
using namespace std;

Ship::Ship():
    _heading(NORTH),
    _velocity(0)
{
    SCREEN_SIZE.w = 640;
    SCREEN_SIZE.h = 360;
    _spriteSheet = IMG_Load("imgs/SpaceShips_on_transparency.png");
    _selectionSpriteSheet = IMG_Load("imgs/SpaceShips_selected_on_transparency.png");
    SDL_Rect masks[4] = {
        {17,10,47,47},
        {63,10,47,47},
        {113,159,45,45},
        {366,311,58,40},
        };
    
    _clipMask = masks[rand() % 4];
    BoundingBox.x = rand() % SCREEN_SIZE.w;
    BoundingBox.y = rand() % SCREEN_SIZE.h;
    _isSelected = false;
}

Ship::~Ship()
{
    //SDL_FreeSurface(_spriteSheet);
}

void Ship::Render(SDL_Surface* screen) const
{
    SDL_Surface* ship_surface;
    if(_isSelected)
        ship_surface = _selectionSpriteSheet;
    else
        ship_surface = _spriteSheet;
    
    switch(_heading)
    {
        case NORTH:
            //Do nothing
            break;
        case SOUTH:
            ship_surface = rotateSurface90Degrees(ship_surface, 2);
            break;
        case EAST:
            ship_surface = rotateSurface90Degrees(ship_surface, 1);
            break;
        case WEST:
            ship_surface = rotateSurface90Degrees(ship_surface, 3);
            break;
    }
    RenderUtility::apply_surface(BoundingBox.x, BoundingBox.y, ship_surface, screen, &_clipMask);

}

void Ship::UpdatePosition() 
{    
    switch(_heading)
    {
        case NORTH:
            BoundingBox.y -= _velocity;
            break;
        case SOUTH:
            BoundingBox.y += _velocity;
            break;
        case EAST:
            BoundingBox.x += _velocity;
            break;
        case WEST:
            BoundingBox.x -= _velocity;
            break;
    }

    //Check for boundaries
    if(BoundingBox.x > SCREEN_SIZE.w)
        BoundingBox.x = 0; //Teleport to other side
    else if(BoundingBox.x < 0)
        BoundingBox.x = SCREEN_SIZE.w;

    if(BoundingBox.y > SCREEN_SIZE.h)
        BoundingBox.y = 0;
    else if(BoundingBox.y < 0)
        BoundingBox.y = SCREEN_SIZE.h;

}

void Ship::Accl( int value)
{
    _velocity += value;
}

void Ship::Select()
{
    _isSelected = true;
}

void Ship::UnSelect()
{
    _isSelected = false;
}

void Ship::Turn(Direction n)
{
    _heading = n;
}

