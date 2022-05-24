#include "Boss.h"

using namespace std;

const float defaultDelta = 0.1;

Boss_02::Boss_02()
{
    started = false;
    y_delta_ = 0.1;
    timeToStart = TIME_BOSS_02_START; /// 1 phút
    standTime = 1000*4; /// 6s
    nextTimeToMove = timeToStart + standTime;
    standing = true;
    upDirect_standing = false;
    countMove_standing = 0;

    blood = 10;
    died = false;

    left = right = 0;

    child[0] = child[1] = NULL;
}

Boss_02::~Boss_02()
{

}
void Boss_02::initBloodBar(SDL_Renderer* renderer)
{
    bloodBar.LoadImg("Image//BossBloodBar.png",renderer);
    bloodBar.setClips(0,1,10);
    bloodBar.setDesRect(0,0,desRect_.w, 0);
}
void Boss_02::init(SDL_Renderer* renderer, const int &left_, const int &right_)
{
    LoadImg("Image//Boss_02.png", renderer);
    left = left_;
    right = right_;

    int w = 2*(right - left)/5;
    int x = left + (right - left)/2 - w/2;
    setDesRect(x,-300,w,0);

    initBloodBar(renderer);
}
bool Boss_02::touchBottom()
{
    return y_pos_ + desRect_.h + bloodBar.GetRect().h + 5> SCREEN_HEIGHT;
}

bool Boss_02::touchTop()
{
    if(!started)
        return y_pos_ >= 10.0;
    return y_pos_ <= 10.0;
}
void Boss_02::downward(float delta)
{
    setDelta(0,delta);
}

void Boss_02::upward(float delta)
{
    setDelta(0, - delta);
}
bool Boss_02::DecBlood()
{
    -- blood;
    if(blood <= 0)
    {
        died = true;
        return false;
    }
    bloodBar.nextFrame(1);
    return true;
}
bool Boss_02::run(const int &currentTime)
{
    if(died) return false;
    if(currentTime >= nextTimeToMove)
    {
        if(touchBottom())
            upward(defaultDelta);
        else if(touchTop())
        {
            nextTimeToMove = currentTime + Rand(2,standTime);
            if(!started)
                started = true;
            else downward(defaultDelta);
        }
        MoveDelta();
    }
    return true;
}

void Boss_02::renderBoss(SDL_Renderer* renderer)
{
    if(died) return;
    Render(renderer,NULL,NULL);
    bloodBar.setPosition(desRect_.x, desRect_.y + desRect_.h + 5);
    bloodBar.Show(renderer);
}

bool Move(Boss_02* node, int high, SDL_Renderer* renderer, const int &currentTime)
{
    if(node->died)
    {
        if(high >= 4)//min(5, 1 + int(max(0,(currentTime - TIME_BOSS_02_START)) / (1000*60*3))))
            return false;
        int left = node->left;
        int right = node->right;

        int res = (right - left)/3;
        int L,R;
        for(int i=0; i<2; ++i)
        {
            if(i==0) L = left, R = left + 2*res;
            else L = left + res, R = right;
            if(node->child[i] == NULL)
            {
                node->child[i] = new Boss_02;
                node->child[i]->init(renderer,L,R);
            }
            Move(node->child[i],high + 1, renderer,currentTime);
        }
    }
    else node->run(currentTime);
}
int BossCheckCollisionWithFairy(Boss_02* node, Fairy* fairy, const int &high)
{
    if(!(node->died))
    {
        if(fairy->checkCollisionWithThreat(node->GetRect(),5))
        {
            node->upward(defaultDelta);
            node->started = true;
            return 5 - high + 1;
        }
    }
    int res = 0;
    for(int i=0; i<2; ++i)
        if(node->child[i] != NULL)
            res = max(res,BossCheckCollisionWithFairy(node->child[i], fairy, high + 1));
    return res;
}
bool BossCheckCollisionWithBullet(Boss_02* node, Fairy* fairy)
{
    if(!(node->died))
    {
        SDL_Rect boss = node->GetRect();
        if(boss.y + boss.h <= 10) return false;
        if(fairy->checkBulletCollision(boss))
        {
            node->DecBlood();
            return true;
        }
    }
    bool ok = false;
    for(int i=0; i<2; ++i)
        if(node->child[i] != NULL)
            ok |= BossCheckCollisionWithBullet(node->child[i], fairy);
    return ok;
}
void Render(Boss_02* node, SDL_Renderer* renderer)
{
    if(!(node->died))
    {
        node -> renderBoss(renderer);
        return;
    }
    for(int i=0; i<2; ++i)
        if(node->child[i] != NULL)
            Render(node->child[i], renderer);
}
