#include "RenderManager.h"

RenderManager::RenderManager()
    : WINDOW_WIDTH(640), 
      WINDOW_HEIGHT(480), 
      WINDOW_TITLE("Spatial Databases w/ SQLite3 Edition")
{
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    close_requested = false;
   
}


bool RenderManager::render_frame()
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

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        pixelRGBA(screen, 10, 15, 255, 255, 255, 255);

        lineRGBA(screen,
                20, 10,
                70, 90,
                255, 0, 0, 255);

        trigonRGBA(screen,
                500, 50,
                550, 200,
                600, 150,
                0, 255, 255, 255);

        filledTrigonRGBA(screen,
                200, 200,
                300, 50,    
                400, 200,
                0, 0, 255, 255);

        rectangleRGBA(screen,
                -10, 300,
                100, 380,
                0, 255, 0, 255);

        boxRGBA(screen,
                210, 76,
                325, 300,
                255, 0, 0, 150);

        ellipseRGBA(screen,
                600, 400,
                50, 90,
                255, 255, 0, 200);

        filledEllipseRGBA(screen,
                600, 400,
                25, 150,
                0, 255, 0, 255);

        short x[6] = { 350, 275, 300, 325, 350, 400 };
        short y[6] = { 325, 325, 390, 390, 375, 300 };

        polygonRGBA(screen,
                x, y,
                6,
                255, 255, 255, 155);

        short s[5] = { 400, 450, 450, 425, 300 };
        short t[5] = { 400, 410, 450, 425, 500};

        filledPolygonRGBA(screen,
                s, t,
                5,
                255, 0, 255, 155);

        SDL_Flip(screen);
        return close_requested;

}

