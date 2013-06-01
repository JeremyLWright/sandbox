/**
 * @brief General Render Manager for drawing to an SDL Surface.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <map>
#include <SDL/SDL.h>
#include <memory>
#include <SDL/SDL_ttf.h>
#include <vector>
#include "Ship.h"
#include "TextBox.h"
#include "FramerateUtility.h"

using namespace std;


class RenderManager {
    public:
        RenderManager();
        virtual ~RenderManager();
        bool close_requested;
        bool render_frame();
        void selectShip(int shipNumber);
        void unSelectShip(int shipNumber);
        void acclShip(int speed);
        void turnShip(char c);
    protected:
        const int WINDOW_WIDTH;
        const int WINDOW_HEIGHT;
        const char* WINDOW_TITLE;
        SDL_Surface* screen;
        SDL_Surface* background;
        SDL_Event event;
        TTF_Font* font;
        map<string, SDL_Color> _pallet;
    private:
        vector<shared_ptr<Ship>> _worldShips;
        int _workingShipIdx;
        shared_ptr<TextBox> _eventWindow;
        shared_ptr<TextBox> _frameWindow;
        void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL  );
        FramerateUtility<10> fps;

};

#endif
