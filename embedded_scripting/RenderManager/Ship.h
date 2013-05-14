/**
 * @brief Concrete Class for Rendering a ship.
 *
 * @par
 * Copyright Jeremy Wright (c) 2012 
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _SHIP
#define _SHIP
#include <SDL/SDL_image.h>
#include <memory>

class Ship
{
public:
    enum Direction {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    Ship();
    virtual ~Ship();
    virtual void Render(SDL_Surface* screen) const;
    virtual void UpdatePosition();
    virtual void Accl(int value);
    void Select();
    void UnSelect();
    void Turn(Direction n);
private:
    bool _isSelected;
    Direction _heading;
    int _velocity; 
    SDL_Rect BoundingBox;
    SDL_Rect SCREEN_SIZE;
    SDL_Surface* _spriteSheet;
    SDL_Surface* _selectionSpriteSheet;
    SDL_Rect _clipMask;
};

#endif /* end of include guard: _SHIP */
