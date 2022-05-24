#include "CommonFunction.h"

using namespace std;

void GetError()
{
    cout<<"SDL Error: "<<SDL_GetError()<<'\n';
}

int Rand(int l,int r)
{
    if(l>r)return l;
    //srand(time(NULL));
    ll res= rand()%2 + 1ll*(1ll*rand()*rand()%MOD+ rand()%MOD)*rand()%MOD;
    return l + res%(r-l+1);
}

bool checkInside(SDL_Rect rect)
{
    int x1 = rect.x;
    int x2 = rect.x + rect.w;
    int y1 = rect.y;
    int y2 = rect.x + rect.h;
    return !((x1>SCREEN_WIDTH)||(x2<0)||(y1>SCREEN_HEIGHT)||(y2<0));
}

bool checkCollision(SDL_Rect rect_1, SDL_Rect rect_2,int delta)
{
    /* (x1,y1) ________ (x2,y1)
              |        |
              |        |
       (x1,y2)|________|(x2,y2)
    */
    if((!checkInside(rect_1))||(!checkInside(rect_2)))
        return false;
    int rect_1_x1 = rect_1.x;
    int rect_1_x2 = rect_1.x + rect_1.w;
    int rect_1_y1 = rect_1.y;
    int rect_1_y2 = rect_1.y + rect_1.h;

    int rect_2_x1 = rect_2.x;
    int rect_2_x2 = rect_2.x + rect_2.w;
    int rect_2_y1 = rect_2.y;
    int rect_2_y2 = rect_2.y + rect_2.h;

    if((rect_1_x2 - delta < rect_2_x1)
            ||(rect_2_x2 - delta < rect_1_x1)
            ||(rect_1_y2 - delta < rect_2_y1)
            ||(rect_2_y2 - delta < rect_1_y1))
        return false;
    return true;
}

string numberToString(const int &number, const int &len)
{
    string t = "";
    int num = number;
    for(; num >0 ; num/=10)
        t = char(num%10 + '0') + t;
    while(t.size()<len) t = '0' + t;
    return t;
}
bool checkFocusWithRect(const int& x, const int &y, const SDL_Rect &rect)
{
    return (rect.x <= x && x <= rect.x + rect.w)
           && (rect.y <= y && y <= rect.y + rect.h);
}

int ShowMenu(SDL_Renderer* renderer, SDL_Event& event)
{
    BaseObject bg_menu;
    bg_menu.LoadImg("Image//menu//menu_bg.png",renderer);
    SDL_Texture* bg_menu_texture = bg_menu.GetTexture();

    Text button [2];
    bool select[2];
    SDL_Rect rect[2];
    for(int i = 0; i<2 ; ++i)
    {
        button[i].setFont("font//BiggerSummerFest-3zK7Z.ttf", 40);
        button[i].setColor(Green);
        select[i] = false;
    }
    button[0].loadText(renderer,"Play");
    button[1].loadText(renderer,"Exit");

    button[0].setPosition(130,433);
    button[1].setPosition(132,500);

    rect[0] = button[0].getDesRect();
    rect[1] = button[1].getDesRect();

    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return -1;
            case SDL_MOUSEMOTION:
            {
                int mouse_x = event.motion.x;
                int mouse_y = event.motion.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(!select[i])
                        {
                            select[i] = true;
                            button[i].setColor(White);
                        }
                    }
                    else
                    {
                        if(select[i])
                        {
                            select[i] = false;
                            button[i].setColor(Green);
                        }
                    }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(i==0) return 1;
                        else return -1;
                    }
            }
            break;
            default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        button[0].loadText(renderer,"Play");
        button[1].loadText(renderer,"Exit");

        SDL_RenderCopy(renderer, bg_menu_texture,NULL,&SCREEN);
        for(int i = 0; i<2 ; ++i)
            button[i].Render(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}

int ShowQuitGame(SDL_Renderer* renderer, SDL_Event& event)
{
    BaseObject bg_quitGame;
    bg_quitGame.LoadImg("Image//quitGame.png",renderer);
    SDL_Texture* bg_quitGame_texture = bg_quitGame.GetTexture();

    Text title[2];
    for(int i = 0; i< 2; ++i)
    {
        title[i].setFont("font//BiggerSummerFest-3zK7Z.ttf", 30);
        title[i].setColor(Green);
    }
    title[0].loadText(renderer, "Please!!!");
    title[1].loadText(renderer, "Keep playing :<");

    title[0].setPosition(100,180);
    title[1].setPosition(60,230);

    Text button [2];
    bool select[2];
    SDL_Rect rect[2];
    for(int i = 0; i<2 ; ++i)
    {
        button[i].setFont("font//BiggerSummerFest-3zK7Z.ttf", 40);
        button[i].setColor(Green);
        select[i] = false;
    }
    button[0].loadText(renderer,"Yes");
    button[1].loadText(renderer,"No");

    button[0].setPosition(138,355);
    button[1].setPosition(145,418);

    rect[0] = button[0].getDesRect();
    rect[1] = button[1].getDesRect();

    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return -1;
            case SDL_MOUSEMOTION:
            {
                int mouse_x = event.motion.x;
                int mouse_y = event.motion.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(!select[i])
                        {
                            select[i] = true;
                            button[i].setColor(White);
                        }
                    }
                    else
                    {
                        if(select[i])
                        {
                            select[i] = false;
                            button[i].setColor(Green);
                        }
                    }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(i==0) return 1;
                        else return -1;
                    }
            }
            break;
            default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        button[0].loadText(renderer,"Yes");
        button[1].loadText(renderer,"No");

        SDL_RenderCopy(renderer, bg_quitGame_texture,NULL,&SCREEN);
        for(int i = 0; i<2 ; ++i)
            button[i].Render(renderer);
        title[0].Render(renderer);
        title[1].Render(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}

int ShowLoseGame(SDL_Renderer* renderer, SDL_Event& event)
{
    BaseObject bg_loseGame;
    bg_loseGame.LoadImg("Image//loseGame.png",renderer);
    SDL_Texture* bg_loseGame_texture = bg_loseGame.GetTexture();

    Text title[3];
    for(int i = 0; i< 3; ++i)
    {
        title[i].setFont("font//BiggerSummerFest-3zK7Z.ttf", 18);
        title[i].setColor(Green);
    }
    title[0].loadText(renderer, "Do you want to exchange");
    title[1].loadText(renderer, "coins for lives");
    title[2].loadText(renderer, "to continue playing?");

    title[0].setPosition(55,180);
    title[1].setPosition(90,210);
    title[2].setPosition(70,240);

    Text button [2];
    bool select[2];
    SDL_Rect rect[2];
    for(int i = 0; i<2 ; ++i)
    {
        button[i].setFont("font//BiggerSummerFest-3zK7Z.ttf", 40);
        button[i].setColor(Green);
        select[i] = false;
    }
    button[0].loadText(renderer,"Yes");
    button[1].loadText(renderer,"No");

    button[0].setPosition(135,355);
    button[1].setPosition(145,417);

    rect[0] = button[0].getDesRect();
    rect[1] = button[1].getDesRect();

    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return -1;
            case SDL_MOUSEMOTION:
            {
                int mouse_x = event.motion.x;
                int mouse_y = event.motion.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(!select[i])
                        {
                            select[i] = true;
                            button[i].setColor(White);
                        }
                    }
                    else
                    {
                        if(select[i])
                        {
                            select[i] = false;
                            button[i].setColor(Green);
                        }
                    }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                for(int i = 0 ; i<2 ; ++i)
                    if(checkFocusWithRect(mouse_x, mouse_y, rect[i]))
                    {
                        if(i==0) return 1;
                        else return -1;
                    }
            }
            break;
            default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        button[0].loadText(renderer,"Yes");
        button[1].loadText(renderer,"No");

        SDL_RenderCopy(renderer, bg_loseGame_texture,NULL,&SCREEN);
        for(int i = 0; i<2 ; ++i)
            button[i].Render(renderer);
        title[0].Render(renderer);
        title[1].Render(renderer);
        title[2].Render(renderer);
        SDL_RenderPresent(renderer);
    }
    return 0;
}
