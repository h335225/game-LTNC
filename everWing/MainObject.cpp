#include "MainObject.h"

using namespace std;

MainObject::MainObject()
{
    leftMargin = 0;
    num_col_frame_ = num_row_frame_ = 1;
    time_next_frame_ = 0;
    frame_ = 0;
    width_frame_ = height_frame_ = 0;
    status_ = -1;
}

MainObject::~MainObject()
{

}

void MainObject::RandomStartPosition()
{
    //srand(time(NULL));
    desRect_.x = x_pos_ = leftMargin + Rand(0,4)*67;
    desRect_.y = y_pos_ = - (1 + Rand(0,8))*80;
}

bool MainObject::LoadImg(string path, SDL_Renderer* renderer)
{
    bool ok = BaseObject::LoadImg(path,renderer);

    if(ok)
    {
        width_frame_ = srcRect_.w;
        height_frame_ = srcRect_.h;
    }
    return ok;
}

void MainObject::setClips(const int &timeNextFrame, const int &numColFrame, const int &numRowFrame)
{
    time_next_frame_= timeNextFrame;
    num_col_frame_ = numColFrame;
    num_row_frame_ = numRowFrame;
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0; i< max(num_col_frame_, num_row_frame_); ++i)
        {
            frame_clip_[i].x = ((num_col_frame_==1)?(0):(i*width_frame_/num_col_frame_));
            frame_clip_[i].y = ((num_row_frame_==1)?(0):(i*height_frame_/num_row_frame_));
            frame_clip_[i].w = width_frame_/num_col_frame_;
            frame_clip_[i].h = height_frame_/num_row_frame_;
        }
        desRect_.w = width_frame_/num_col_frame_;
        desRect_.h = height_frame_/num_row_frame_;
    }
}

void MainObject::Show(SDL_Renderer* renderer)
{
    Move();
    if(desRect_.y + desRect_.h <0) return;

    SDL_RenderCopy(renderer,texture_, &frame_clip_[frame_], &desRect_);
}

void MainObject::Reset()
{
    if(y_pos_ > SCREEN_HEIGHT)
    {
        RandomStartPosition();
        if(SDL_GetTicks()>1000*30)
        {
            setDelta(0,0);
        }
    }
}
void MainObject::nextFrame(const int &delta)
{
    frame_ =( frame_ + delta)%(max(num_col_frame_, num_row_frame_));
}
void MainObject::preFrame(const int &delta)
{
    frame_ =( frame_ - delta)%(max(num_col_frame_, num_row_frame_));
    if(frame_<0)
        frame_ += (max(num_col_frame_, num_row_frame_));
}
void MainObject::autoNextFrame(const int &deltaTime)
{
    if(deltaTime == 0)return;
    if(SDL_GetTicks() % deltaTime == 0)
        nextFrame(1);
}
void MainObject::Move()
{
    MoveDelta();
    if(x_delta_)
    {
        x_delta_ += INC_SPEED;
        y_delta_ += INC_SPEED;
    }
    autoNextFrame(time_next_frame_);
    Reset();
}
