#include "BaseObject.h"
#include "CommonFunction.h"

BaseObject::BaseObject()
{
    texture_ = NULL;
    srcRect_ = desRect_ = {0,0,0,0};
    x_delta_ = 0;
    y_delta_ = 0.04;
    x_pos_ = 0;
    y_pos_ = 0;
}

BaseObject::~BaseObject()
{
    SDL_DestroyTexture(texture_);
    texture_=NULL;
    srcRect_ = desRect_ = {0,0,0,0};
}
bool BaseObject::checkCollision_(SDL_Rect rect, int delta)
{
    return checkCollision(desRect_, rect, delta);
}
bool BaseObject::LoadImg(string pathIMG, SDL_Renderer* renderer)
{
    SDL_Surface* tmpSurface = IMG_Load(pathIMG.c_str());
    if(!tmpSurface)
    {
        GetError();
        return false;
    }
    SDL_SetColorKey(tmpSurface,SDL_TRUE, SDL_MapRGB(tmpSurface->format,COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    if(!newTexture)
    {
        GetError();
        return false;
    }
    srcRect_.w = tmpSurface->w;
    srcRect_.h = tmpSurface->h;
    if(desRect_.w == 0)
    {
        desRect_.w = tmpSurface->w;
        desRect_.h = tmpSurface->h;
    }
    texture_ = newTexture;
    SDL_FreeSurface(tmpSurface);
    return true;
}

void BaseObject::Render(SDL_Renderer* renderer, SDL_Rect* srcRect, SDL_Rect* desRect)
{
    if(desRect==NULL)desRect = (&desRect_);
    if(!checkInside(*desRect)) return ;

    if(srcRect==NULL)srcRect = (&srcRect_);
    SDL_RenderCopy(renderer,texture_, srcRect, desRect);
}


