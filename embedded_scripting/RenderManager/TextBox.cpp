#include "TextBox.h"
#include <stdexcept>
#include <iostream>
#include "RenderUtility.h"
TextBox::~TextBox()
{
}

TextBox::TextBox(SDL_Rect position, TTF_Font* font):
    _position(position),
    _font(font)
{
    _numLines = _position.h / TTF_FontLineSkip(font);
}

void TextBox::AddMessage(string msg, SDL_Color color)
{
    if(_lines.size() == _numLines)
    {
        _lines.pop_back();
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(_font, msg.c_str(), color);
    if(textSurface == 0)
        throw runtime_error("Could not Initalize Text Screen");
    _lines.push_front(textSurface);
}

void TextBox::Render(SDL_Surface* screen) const
{
    auto lineStart = _position.y;
    for(auto line: _lines)
    {
        RenderUtility::apply_surface(_position.x, lineStart, line, screen, NULL);
        lineStart += TTF_FontLineSkip(_font);
    } 
}

