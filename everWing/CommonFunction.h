#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Sound.h"
#include <bits/stdc++.h>
#include "bullet.h"
#include "text.h"

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 360;//720
const int SCREEN_HEIGHT = 640;//1280
const int SCREEN_BPP = 32;
const SDL_Rect SCREEN = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
static int currentTime;

#define ll long long
const int MOD = 1e9 + 7;

const SDL_Color SaddleBrown =  {139, 69, 19};
const SDL_Color Black =  {0,0,0};
const SDL_Color White =  {255,255,255};
const SDL_Color Green =  {0,153,76};

static Chunk roar; /// tiếng gầm

using namespace std;

void GetError();
int Rand(int l,int r);
bool checkCollision(SDL_Rect rect_1, SDL_Rect rect_2, int delta);
bool checkInside(SDL_Rect rect);
string numberToString(const int &number, const int &len);
bool checkFocusWithRect(const int& x, const int &y, const SDL_Rect &rect);

int ShowMenu(SDL_Renderer* renderer, SDL_Event& event);
int ShowQuitGame(SDL_Renderer* renderer, SDL_Event& event);
int ShowLoseGame(SDL_Renderer* renderer, SDL_Event& event);
#endif // COMMON_FUNCTION_H_
