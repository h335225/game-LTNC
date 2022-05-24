#include "item.h"

Blood::Blood()
{
    countHeart = 5;
}
Blood::~Blood()
{

}
void Blood::init(SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_HEART; ++i)
    {
        heart[i].LoadImg("Image//heart.png", renderer);
        heart[i].setClips(0,1,1);
        heart[i].setDesRect(0,0,28,28);
        heart[i].setLeftMargin(5);
        heart[i].RandomStartPosition();
    }

    bloodBar.LoadImg("Image//BloodBar.png",renderer);
    bloodBar.setClips(0,1,6);
    bloodBar.setDelta(0,0);
    bloodBar.setDesRect(0,0,0,20);
}
void Blood::MoveHeart()
{
    for(int i=0; i<NUMBER_HEART; ++i)
        heart[i].Move();
}
void Blood::IncHeart(const int &delta)
{
    countHeart += delta;
    if(countHeart<=5)
        bloodBar.preFrame(delta);
    else countHeart = 5;
}
bool Blood::DecHeart(const int &delta)
{
    bloodBar.nextFrame(min(countHeart,delta));
    countHeart -= delta;
    if(countHeart <= 0)
    {
        countHeart = 0;
        return false;
    }
    return true;
}
bool Blood::heartCheckCollision(SDL_Rect rect)
{
    for(int i=0; i<NUMBER_HEART; ++i)
        if(heart[i].checkCollision_(rect,5))
        {
            heart[i].RandomStartPosition();
            IncHeart(1);
            coinMusic.play(1);
            return true;
        }
    return false;
}
void Blood::RenderBloodBar(SDL_Renderer* renderer, const SDL_Rect &fairy)
{
    bloodBar.setDesRect(fairy.x, fairy.y + fairy.h + 5, fairy.w, 15);
    bloodBar.Show(renderer);
}
void Blood::RenderHeart(SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_HEART; ++i)
        heart[i].Show(renderer);
}


Money::Money()
{
    countCoin = 0;
}
Money::~Money()
{

}
void Money::InitCoin(SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_COIN; ++i)
    {
        coin[i].LoadImg("Image//xu.png",renderer);
        coin[i].setClips(60,10,1);
        coin[i].setLeftMargin(15);
        coin[i].setDesRect(0,0,28,28);
        coin[i].RandomStartPosition();
    }
    coinMusic.loadMusic("Sound//coin.mp3");
}
void Money::InitNumberMoney(SDL_Renderer* renderer)
{
    coinChest.LoadImg("Image//coinChest.png",renderer);
    numberMoney.setColor(Black);
    numberMoney.setFont("font//SunnyspellsRegular-MV9ze.ttf",50);
}
void Money::init(SDL_Renderer* renderer)
{
    InitNumberMoney(renderer);
    InitCoin(renderer);
}
bool Money::coinCheckCollision(const SDL_Rect &fairyRect)
{
    for(int i=0; i<NUMBER_COIN; ++i)
        if(coin[i].checkCollision_(fairyRect,5))
        {
            coinMusic.play(1);
            coin[i].RandomStartPosition();
            ++countCoin;
            return true;
        }
    return false;
}
void Money::moveCoin()
{
    for(int i=0; i<NUMBER_COIN; ++i)
        coin[i].Move();
}
void Money::RenderNumberCoin(SDL_Renderer* renderer)
{
    int x=200,y=0;
    coinChest.setDesRect(x,y,0,0);
    coinChest.Render(renderer, NULL,NULL);

    x+= coinChest.GetRect().w;
    numberMoney.setPosition(x,y);
    string t= numberToString(countCoin,4);

    numberMoney.loadText(renderer, t.c_str());
    numberMoney.Render(renderer);
}
void Money::RenderCoin(SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_COIN; ++i)
        coin[i].Show(renderer);
}
void Money::Render(SDL_Renderer* renderer)
{
    RenderCoin(renderer);
    RenderNumberCoin(renderer);
}
