#ifndef BULLET_H_
#define BULLET_H_
#include "BaseObject.h"
#include "CommonFunction.h"
#include "Sound.h"

using namespace std;

const int NUMBER_BULLET = 35;

class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();
    bool unfired; /// chưa bắn
    void setNumericalOrder(int number);
    bool checkBulletCollision(SDL_Rect threat);
    bool Move();
    void setStartPositionBullet(const SDL_Rect &fairyRect);
private:
    int numericalOrder; // số thứ tự
};

class BulletAction
{
public:
    BulletAction();
    ~BulletAction();
    void Init(SDL_Renderer* renderer);
    bool LoadChunk(string pathFile, int volume);
    void LoadImage(string pathFile, SDL_Renderer* renderer);
    void pushBackBullet(int posBullet);
    int popBackBullet();
    void fire(SDL_Renderer* renderer, const SDL_Rect &fairyRect);
    void moveAllFireBullet(const SDL_Rect &fairyRect);
    void showAllFireBullet(SDL_Renderer* renderer);

    bool checkCollision(SDL_Rect threat, SDL_Rect fairyRect);
private:
    Bullet bullet[NUMBER_BULLET];
    int numUnfiredBullet = -1;
    int unfiredBullet [NUMBER_BULLET];
    Chunk BulletChunk;
};

#endif // BULLET_H_
