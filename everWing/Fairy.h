#ifndef FAIRY_H_
#define FAIRY_H_

#include "MainObject.h"
#include "bullet.h"

#define PLAYER_SPEED 0.25

using namespace std;

class protectiveCircle: public BaseObject
{
public:
    protectiveCircle();
    ~protectiveCircle();

    void init(SDL_Renderer* renderer);
    void setTimeToEndProtection();
    bool isRunning();
    void Move(const SDL_Rect &fairyRect);
    void renderProtectiveCircle(SDL_Renderer* renderer);
private:
    int timeToEndProtection;
    int timeProtect;
};


class Fairy: public MainObject
{
public:
    Fairy();
    ~Fairy();
    void Init(SDL_Renderer* renderer);
    bool checkBulletCollision(SDL_Rect threat);
    bool checkCollisionWithThreat(SDL_Rect threat, int delta);
    void InputAction(SDL_Event event, SDL_Renderer* renderer);
    void MoveFairy();
    void render(SDL_Renderer* renderer);
    bool protect()
    {
        return protectCircle.isRunning();
    }
    protectiveCircle protectCircle;
private:
    BulletAction allBullet;
};

#endif // FAIRY_H_
