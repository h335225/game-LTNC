#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>

using namespace std;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void setPosition(int x,int y)
    {
        desRect_.x = x_pos_ = x;
        desRect_.y = y_pos_ = y;
    }
    void setDesRect(const int &x,const int &y, const int &w, const int &h)
    {
        x_pos_ = desRect_.x = x;
        y_pos_ = desRect_.y = y;
        if(w != 0)
        {
            desRect_.h = ((h)?(h):((w*desRect_.h)/desRect_.w));
            desRect_.w=w;
        }else if(h != 0)
        {
            desRect_.w = (h*desRect_.w)/desRect_.h;
            desRect_.h = h;
        }
    };
    SDL_Rect GetRect()  /// trả về hcn chứ hình ảnh
    {
        return desRect_;
    };
    SDL_Texture* GetTexture()
    {
        return texture_;
    };
    void setDelta(float x_delta,float y_delta)
    {
        x_delta_ = x_delta;
        y_delta_ = y_delta;
    }
    void MoveDelta()
    {
        x_pos_ += x_delta_;
        y_pos_ += y_delta_;
        desRect_.x = x_pos_;
        desRect_.y = y_pos_;
    }
    bool checkCollision_(SDL_Rect rect, int delta);
    bool LoadImg(string pathIMG, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer, SDL_Rect* srcRect, SDL_Rect* desRect);
protected:
    SDL_Rect srcRect_; /// phần của texture muốn render lên mh
    SDL_Rect desRect_; /// vị trí muốn render lên mh
    SDL_Texture* texture_;
    float x_delta_, y_delta_;
    float x_pos_, y_pos_;
};
#endif // BASE_OBJECT_H_
