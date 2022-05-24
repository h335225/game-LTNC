#include "text.h"
#include "CommonFunction.h"

Text::Text()
{
    font = NULL;
    surface = NULL;
    texture = NULL;
    color = Black;
    desRect = srcRect = {0,0,0,0};
}
Text::~Text()
{
    font = NULL;
    SDL_DestroyTexture(texture);
    desRect = srcRect = {0,0,0,0};
}
bool Text::setFont(const string &pathFile, const int &fontSize)
{
    font = TTF_OpenFont(pathFile.c_str(),fontSize);
    if(font == NULL)
    {
        cout<<"Font : "<<TTF_GetError()<<'\n';
        return false;
    }
    return true;
}
void Text::setColor(const SDL_Color color_)
{
    color = color_;
}
void Text::setColor(const int &r, const int &g, const int &b)
{
    color = {r,g,b};
}
bool Text::loadText(SDL_Renderer* renderer, const string &text)
{
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, text.c_str(),color);
    // surface = TTF_RenderText_Shaded(font, text.c_str(), color, {100,100,100});
    if(surface == NULL)
    {
        cout<<TTF_GetError()<<'\n';
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == NULL)
    {
        cout<<"Text error : ";
        GetError();
        return false;
    }
    TTF_SizeText(font, text.c_str(), &srcRect.w, &srcRect.h);

    if(desRect.w == 0)
    {
        desRect.w = srcRect.w;
        desRect.h = srcRect.h;
        cout<<srcRect.w<<' '<<srcRect.h<<'\n';
    }

    return true;
}
void Text::setPosition(const int &x, const int &y)
{
    desRect.x = x;
    desRect.y = y;
}
SDL_Rect Text:: getDesRect()
{
    return desRect;
}
void Text::setDesRect(const SDL_Rect &rect)
{
    desRect = rect;
}
void Text::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &srcRect, &desRect);
}


