#ifndef BOSS_H
#define BOSS_H
#include "Sound.h"
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Fairy.h"
#include "item.h"

using namespace std;

static int TIME_BOSS_02_START = 1000*60*3; /// 3p

class Boss_02 : public BaseObject
{
public:
    bool started;
    bool died;
    Boss_02* child[2];
    int left, right;

    Boss_02 ();
    ~Boss_02 ();

    void init(SDL_Renderer* renderer,const int &left, const int &right);
    void initBloodBar(SDL_Renderer* renderer);
    bool touchBottom(); /// kiểm tra quái vật đã chạm đáy hay chưa
    bool touchTop(); /// kiểm tra quái vật đã chạm đỉnh hay chưa
    void downward(float delta);
    void upward(float delta);
    bool DecBlood();
    bool run(const int &currentTime);
    void renderBoss(SDL_Renderer* renderer);
private:
    int timeToStart;
    int standTime;
    int nextTimeToMove;
    bool standing;
    int countMove_standing;
    bool upDirect_standing; /// hướng di chuyển tại chỗ

    MainObject bloodBar;
    int blood;
};

bool Move(Boss_02* node, int high, SDL_Renderer* renderer, const int &currentTime);
int BossCheckCollisionWithFairy(Boss_02* node, Fairy* fairy,const int &high);
bool BossCheckCollisionWithBullet(Boss_02* node, Fairy* fairy);
void Render(Boss_02* node, SDL_Renderer* renderer);
#endif // BOSS_H
