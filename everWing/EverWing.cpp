#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "BaseObject.h"
#include "MainObject.h"
#include "CommonFunction.h"
#include "Sound.h"
#include "Boss.h"
#include "bullet.h"
#include "Fairy.h"
#include "item.h"
#include "text.h"
BaseObject g_background;

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        GetError();
        return false;
    }

    g_window = SDL_CreateWindow("EverWing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!g_window)
    {
        GetError();
        return false;
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(!g_renderer)
    {
        GetError();
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout<<Mix_GetError()<<'\n';
        return false;
    }
    if (TTF_Init() < 0)
    {
        cout<<TTF_GetError()<<'\n';
        return false;
    }
    return true;
}

void CleanUp()
{
    g_background.~BaseObject();

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
}
bool LoadBackground()
{
    if(g_background.LoadImg("Image//map//Map_1.jpg",g_renderer))
    {
        g_background.setDesRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        return true;
    }
    return false;
}

MainObject monster[20];
int numMonster = 20;
void InitMonster()
{
    srand(time(NULL));
    for(int i=0; i<numMonster; ++i)
    {
        int x = ((i<3)?(1+i%3):(Rand(1,3)));
        string path="Image//Monster_0";
        path+= char(x+'0');
        path+=".png";

        monster[i].LoadImg(path,g_renderer);
        monster[i].setClips(0,1,1);
        monster[i].setDesRect(0,0,67,67);
        monster[i].setLeftMargin(4.1);
        monster[i].RandomStartPosition();
    }
}

Fairy fairy;
Money money;


Boss_02* rootBoss_02;
Blood blood;
void InitAll()
{
    roar.loadChunk("Sound//boss_02.wav",50);
    rootBoss_02 = new Boss_02;
    rootBoss_02->init(g_renderer,0,SCREEN_WIDTH);
    InitMonster();
    money.init(g_renderer);
    fairy.Init(g_renderer);
    blood.init(g_renderer);
}

/// trả về 0 là tiếp tục game
/// về -1 là tiên bị thua
int Process(bool &running)
{
    if(!running) return 0;

    fairy.MoveFairy();
    SDL_Rect fairyRect = fairy.GetRect();

    blood.heartCheckCollision(fairyRect);

    for(int i=0; i< 7 + min(13, currentTime/(1000*15)); ++i)
    {
        SDL_Rect monsterRect = monster[i].GetRect();
        if(fairy.checkBulletCollision(monsterRect))
        {
            monster[i].RandomStartPosition();
        }
        if(fairy.checkCollisionWithThreat(monsterRect,10))
        {
            monster[i].RandomStartPosition();
            if(!blood.DecHeart(1))
            {
                running = false;
                return -1;
            }
        }
    }
    money.coinCheckCollision(fairyRect);
//    else

    if(currentTime>= TIME_BOSS_02_START)
    {
        if(!Move(rootBoss_02,1,g_renderer,currentTime))
        {
            return 1;
        }
        else
        {
            if((currentTime == TIME_BOSS_02_START + 500) || (currentTime%8000 == 0))
                roar.play(-1,1);
            BossCheckCollisionWithBullet(rootBoss_02,&fairy);
            if(!fairy.protect())
            {
                int dame = BossCheckCollisionWithFairy(rootBoss_02,&fairy,1);
                if(!blood.DecHeart(dame))
                {
                    running = false;
                    return -1;
                }
            }
        }
    }
    return 0;
}

Text number;
void RenderGame(int type)
{
    SDL_RenderClear(g_renderer);
    g_background.Render(g_renderer, NULL, NULL);
    if(type == -1)
    {
        for(int i=0; i<7 + min(13, currentTime/(1000*15)); ++i)
            monster[i].Show(g_renderer);

        money.RenderCoin(g_renderer);
        blood.RenderHeart(g_renderer);

        Render(rootBoss_02,g_renderer);

        fairy.render(g_renderer);

        money.RenderNumberCoin(g_renderer);
        blood.RenderBloodBar(g_renderer, fairy.GetRect());
    }
    SDL_RenderPresent(g_renderer);
}


int main(int argc, char** argv)
{
    if(!Init())
        return 0;
    if(!LoadBackground())
        return 0;
    InitAll();

    if(ShowMenu(g_renderer, g_event)<0)
    {
        SDL_Delay(1000);
        CleanUp(); //cleans up all initialized subsystems
        SDL_Quit();
        return 0;
    }

    SDL_Delay(300);
    bool running = true;
    while(running)
    {
        int type = 0;
        while(running)
        {
            while(SDL_PollEvent(&g_event))
            {
                if(g_event.type == SDL_QUIT)
                {
                    if(ShowQuitGame(g_renderer, g_event)==-1)
                        running = false;
                }

                fairy.InputAction(g_event, g_renderer);
            }
            currentTime = SDL_GetTicks();
            type = Process(running);
            RenderGame(type);
        }

        if(type == -1)
        {
            if(money.getMoney()>=20)
                if(ShowLoseGame(g_renderer, g_event)==1)
                {
                    running = true;
                    blood.IncHeart(1);
                    money.decCoin(20);
                    fairy.protectCircle.setTimeToEndProtection();
                }
        }
    }
    SDL_Delay(3000);
    CleanUp(); //cleans up all initialized subsystems
    SDL_Quit();
    return 0;
}

