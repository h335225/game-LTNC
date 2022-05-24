#include "bullet.h"

using namespace std;

/// Bullet
/// ___________________________________
Bullet:: Bullet()
{
    unfired = true;
    numericalOrder = 0;
    setDelta(0,-0.32);
    setDesRect(0,0,50,50);
}
Bullet:: ~Bullet()
{

}
void Bullet::setNumericalOrder(int number)
{
    numericalOrder = number;
}
bool Bullet::checkBulletCollision(SDL_Rect threat)
{
    if(unfired) return false;
    if(checkCollision_(threat,10))
    {
        unfired = true;
        return true;
    }
    return false;
}

bool Bullet:: Move()
{
    if(unfired) return false;
    MoveDelta();
    return true;
}
void Bullet:: setStartPositionBullet(const SDL_Rect &fairyRect)
{
    int x = fairyRect.x + (fairyRect.w/2) - (desRect_.w/2);
    int y = fairyRect.y - desRect_.h;
    setPosition(x,y);
}
/// ___________________________________


/// BulletAction
/// ___________________________________
BulletAction::BulletAction()
{

}
BulletAction::~BulletAction()
{

}
void BulletAction::Init(SDL_Renderer* renderer)
{
    LoadChunk("Sound//laser.wav",40);
    LoadImage("Image//bullet.png",renderer);
}
bool BulletAction::LoadChunk(string pathFile, int volume)
{
    return BulletChunk.loadChunk(pathFile,volume);
}
void BulletAction::LoadImage(string pathFile, SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_BULLET; ++i)
    {
        bullet[i].LoadImg(pathFile,renderer);
        pushBackBullet(i);
    }
}
void BulletAction::pushBackBullet(int numericalOrder) /// posBullet là stt của viên đạn thêm vào
{
    numUnfiredBullet++;
    unfiredBullet[ numUnfiredBullet ] = numericalOrder;
    bullet[numericalOrder].unfired = true;
    //cout<<"them vao dan so "<<numericalOrder<<'\n';
}
int BulletAction::popBackBullet()
{
    int numericalOrder = unfiredBullet[numUnfiredBullet];
    bullet[numericalOrder].unfired = false;
    //cout<<"ban ra dan so "<<numericalOrder<<'\n';
    numUnfiredBullet--;
    return numericalOrder;
}
void BulletAction::fire(SDL_Renderer* renderer, const SDL_Rect &fairyRect)
{
    BulletChunk.play(-1,1);
    int numericalOrder = popBackBullet();
    bullet[numericalOrder].setStartPositionBullet(fairyRect);
}

void BulletAction::moveAllFireBullet(const SDL_Rect &fairyRect)
{
    for(int i=0; i<NUMBER_BULLET; ++i)
        if(bullet[i].Move())
        {
            SDL_Rect bulletRect = bullet[i].GetRect();
            if(bulletRect.y + bulletRect.h <0)
                pushBackBullet(i);
        }
}

void BulletAction::showAllFireBullet(SDL_Renderer* renderer)
{
    for(int i=0; i<NUMBER_BULLET; ++i)
        if(!bullet[i].unfired)
            bullet[i].Render(renderer, NULL, NULL);
}

bool BulletAction::checkCollision(SDL_Rect threat, SDL_Rect fairyRect)
{
    bool ok = false;
    for(int i=0; i<NUMBER_BULLET; ++i)
        if(bullet[i].checkBulletCollision(threat))
        {
            pushBackBullet(i);
            ok = true;
        }
    return ok;
}
/// ___________________________________

