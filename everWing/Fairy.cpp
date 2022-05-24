#include "Fairy.h"

protectiveCircle::protectiveCircle()
{
    timeToEndProtection = -1;
    timeProtect = 5000;
}
protectiveCircle::~protectiveCircle()
{

}
void protectiveCircle::init(SDL_Renderer* renderer)
{
    LoadImg("Image//protectiveCircle.png", renderer);
    setDesRect(0,0,130,130);
}
void protectiveCircle::setTimeToEndProtection()
{
    int currentTime = SDL_GetTicks();
    timeToEndProtection = currentTime + timeProtect;
}
bool protectiveCircle::isRunning()
{
    int currentTime = SDL_GetTicks();
    if(currentTime<timeToEndProtection - 100)
        return true;
    return false;
}
void protectiveCircle::Move(const SDL_Rect &fairyRect)
{
    if(isRunning())
    {
        int x = fairyRect.x + (fairyRect.w/2) - (desRect_.w/2);
        int y = fairyRect.y + (fairyRect.h/2) - (desRect_.h/2);
        setPosition(x,y);
    }
}
void protectiveCircle::renderProtectiveCircle(SDL_Renderer* renderer)
{
    if(isRunning())
        Render(renderer, NULL,NULL);
}



Fairy::Fairy()
{

}
Fairy::~Fairy()
{

}
void Fairy::Init(SDL_Renderer* renderer)
{
    LoadImg("Image//Fairy.png",renderer);
    setClips(0,1,1);
    setDelta(0,0);
    setDesRect(0,0,90,0);
    setPosition(190,670);

    protectCircle.init(renderer);
    allBullet.Init(renderer);
}
bool Fairy::checkBulletCollision(SDL_Rect threat)
{
    return allBullet.checkCollision(threat, desRect_);
}
bool Fairy::checkCollisionWithThreat(SDL_Rect threat, int delta)
{
    if(protectCircle.isRunning()) return false;
    if(checkCollision_(threat,delta))
    {
        cout<<"collision with threat \n";
        protectCircle.setTimeToEndProtection();
        protectCircle.Move(desRect_);
       // setPosition(190,670);
        return true;
    }
    return false;
}
void Fairy::InputAction(SDL_Event event, SDL_Renderer* renderer)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_SPACE:
            allBullet.fire(renderer, desRect_);
            break;
        default:
            break;
        };
    }
    break;
    case SDL_MOUSEMOTION:
    {
        x_pos_ = event.motion.x - desRect_.w/2;
        y_pos_ = event.motion.y - desRect_.h/2;
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
        allBullet.fire(renderer, desRect_);
        break;
    default:
        break;
    }
}
void Fairy::MoveFairy()
{
    protectCircle.Move(desRect_);
    allBullet.moveAllFireBullet(desRect_);
}
void Fairy::render(SDL_Renderer* renderer)
{
    Show(renderer);
    protectCircle.renderProtectiveCircle(renderer);
    allBullet.showAllFireBullet(renderer);
}
