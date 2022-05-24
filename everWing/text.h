#ifndef TEXT_H_
#define TEXT_H_

#include <bits/stdc++.h>
#include <SDL_ttf.h>

using namespace std;

class Text
{
public:
    Text();
    ~Text();

    bool setFont(const string &pathFile, const int &fontSize);
    void setColor(const SDL_Color color_);
    void setColor(const int &r, const int &g, const int &b);
    bool loadText(SDL_Renderer* renderer, const string &text);
    void setPosition(const int &x, const int &y);
    void setDesRect(const SDL_Rect &rect);
    SDL_Rect getDesRect();
    void Render(SDL_Renderer* renderer);
private:
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;
    SDL_Rect desRect, srcRect;
};

#endif // TEXT_H_
