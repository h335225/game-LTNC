#include "Sound.h"

using namespace std;

/// MUSIC
bool Music::loadMusic(string path_name)
{
    music = Mix_LoadMUS(path_name.c_str());
    if(music==NULL)
    {
        cout<<Mix_GetError()<<'\n';
        return false;
    }
    return music;
}
bool Music::play(int loops)
{
    if(Mix_PlayMusic(music,loops)<0)
    {
        cout<<Mix_GetError()<<'\n';
        return false;
    }
    return true;
}
/// ***************************


/// CHUNK
bool Chunk::loadChunk(string path_name, int volume)
{
    chunk = Mix_LoadWAV(path_name.c_str());
    if(chunk == NULL)
    {
        cout<<Mix_GetError()<<'\n';
        return false;
    }
    else chunk->volume = volume;
    return true;
}

bool Chunk::play(int channel, int loops)
{
    if(Mix_PlayChannel(channel, chunk, loops)<0)
    {
        cout<<Mix_GetError()<<'\n';
        return false;
    }
    return true;
}
/// ***************************
