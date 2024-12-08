#ifndef __ROBOTRAM__
#define __ROBOTRAM__

#include "dvc_encoder.h"

enum Enum_RobotTram
{
    Encoder_1 = 0,
    Encoder_2 = 1,
    Encoder_3 = 2,
    Encoder_4 = 3,
    Encoder_5 = 4,
};


class Class_RobotTram
{
    public:
    void Init();
    inline float Get_Angle(Enum_RobotTram __ID);
    void Calculate_RobotTram_Angle();
    void RoboTram_Angle_Control_Trasmit();

    protected:
    //五个编码器
    Class_Encoder Encoder[5];
    //机械臂对外角度 右手螺旋定则
    float Angle[5];
    //机械臂上电限位角度
    float Angle_Offset[5] = {-10.f,186.f,186.f,0.f,45.f};

};


float Class_RobotTram::Get_Angle(Enum_RobotTram __ID)
{
    return (Angle[__ID]);
}

#endif

