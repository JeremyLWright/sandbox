#ifndef _RENDERUTILITY
#define _RENDERUTILITY

class RenderUtility {
public:
    RenderUtility (){};
    virtual ~RenderUtility (){};
    static void apply_surface( int x, int y, SDL_Surface const * source, SDL_Surface* destination, SDL_Rect const * clip )
    { 
        //Holds offsets 
        SDL_Rect offset; 
        //Get offsets 
        offset.x = x; 
        offset.y = y; 
        SDL_BlitSurface( const_cast<SDL_Surface*>(source), const_cast<SDL_Rect*>(clip), destination, &offset ); 
    }

private:
    /* data */
};


#endif /* end of include guard: _RENDERUTILITY */
