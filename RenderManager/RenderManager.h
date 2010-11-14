#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "Lemming.h"
#include "Region.h"
#include "SpatialModel.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>


class RenderManager {
    public:
    RenderManager();

    bool close_requested;
    bool render_frame();
    protected:
    void render_lemming(SpatialDB::Lemming& lemming);
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const char* WINDOW_TITLE;
    SDL_Surface* screen;
    SDL_Event event;
    SpatialDB::SpatialModel&  spatial_db;
    
};

#endif
