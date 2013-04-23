/**
 * @brief Small Widget for rendering a text box
 *
 * @par
 * Copyright Jeremy Wright (c) 2012 
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */

#ifndef _TEXTBOX
#define _TEXTBOX

#include <SDL/SDL_ttf.h>
#include <deque>
#include <string>

using namespace std;

class TextBox {
public:
    TextBox (SDL_Rect position, TTF_Font* font);
    virtual ~TextBox ();
    virtual void Render(SDL_Surface* screen) const;
    virtual void AddMessage(string msg, SDL_Color color);
private:
    SDL_Rect const _position;
    deque<SDL_Surface*> _lines;
    TTF_Font* _font;
    int _numLines;
};


#endif /* end of include guard: _TEXTBOX */
