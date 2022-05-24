#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "bullet.h"
#define GRAVITY_SPEED 0.8
//#define MAX_FALL_SPEED 0.1
#define INC_SPEED 0.001

using namespace std;

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    void setClips(const int &timeNextFrame, const int &numColFrame, const int &numRowFrame);

    void setLeftMargin(float res)
    {
        leftMargin = res;
    }
    void RandomStartPosition();

    bool LoadImg(string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);

    void Move();
    void Reset();

    void nextFrame(const int &delta);
    void preFrame(const int &delta);
    void autoNextFrame(const int &deltaTime);

private:

    float leftMargin;

    int width_frame_;
    int height_frame_;
    int time_next_frame_;

    int num_col_frame_; /// số lượng frame theo cột
    int num_row_frame_; /// số lượng frame theo hàng
    SDL_Rect frame_clip_[10];

    int frame_;/// vị trí của frame đang hiển thị
    int status_;/// trạng thái di chuyển sang trái hay phải
};

#endif // MAIN_OBJECT_H_
