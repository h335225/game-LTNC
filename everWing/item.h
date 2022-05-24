#ifndef ITEM_H_
#define ITEM_H_

#include "BaseObject.h"
#include "MainObject.h"
#include "Sound.h"
#include "text.h"

using namespace std;

const int NUMBER_HEART = 2;
const int NUMBER_COIN = 7;
static Music coinMusic;

class Blood
{
public:
    Blood();
    ~Blood();
    void init(SDL_Renderer* renderer);
    void MoveHeart();
    void IncHeart(const int &delta);
    bool DecHeart(const int &delta);
    bool heartCheckCollision(SDL_Rect rect);
    void RenderBloodBar(SDL_Renderer* renderer, const SDL_Rect &fairy);
    void RenderHeart(SDL_Renderer* renderer);
private:
    MainObject heart[NUMBER_HEART];
    MainObject bloodBar;
    int countHeart;
};

class Money: public BaseObject
{
public:
    Money();
    ~Money();
    void InitCoin(SDL_Renderer* renderer);
    void InitNumberMoney(SDL_Renderer* renderer);
    void init(SDL_Renderer* renderer);
    bool coinCheckCollision(const SDL_Rect &fairyRect);
    void decCoin(const int& delta)
    {
        countCoin -= delta;
    }
    int getMoney()
    {
        return countCoin;
    }
    void moveCoin();
    void RenderNumberCoin(SDL_Renderer* renderer);
    void RenderCoin(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
private:
    MainObject coin[NUMBER_COIN];
    BaseObject coinChest;
    int countCoin;
    Text numberMoney;
};
#endif // ITEM_H_
