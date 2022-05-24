#ifndef SOUND_H_
#define SOUND_H_

#include <SDL_mixer.h>
#include <bits/stdc++.h>

using namespace std;

/// MUSIC

class Music
{
public:
    bool loadMusic(string path_name);
    bool play(int loops);
private:
    Mix_Music* music;
};

/// ***************************



/// CHUNK

class Chunk
{
public:
    bool loadChunk(string path_name, int volume);
    bool play(int channel, int loops);
private:
    Mix_Chunk* chunk;
};

/// ***************************
#endif // SOUND_H_
