#ifndef _CRT_GIMBAL_H_
#define _CRT_GIMBAL_H_
#ifdef __cplusplus
#include "dvc_djimotor.h"
#include "alg_pid.h"
enum Enum_Gimbal_Status
{
    Gimbal_Disable,
    Gimbal_Enable,
};
enum Enum_Yaw_Status
{
    Yaw_Disable,
    Yaw_Enable,
};
class Class_Yaw_Motor : public Class_DJI_Motor_GM6020
{
public:
    //变量
    float Yaw_Target_Angle;
    float Yaw_Now_Angle;
    int16_t Yaw_Target_Encoder; 
    Enum_Yaw_Status yaw_status;
    //函数
    void Yaw_Target_Angle_To_Encoder();
    void Calculate_Yaw_Now_Angle();
    inline void Set_Yaw_Target_Angle(float _Yaw_Target_Angle);
    void TIM_PID_PeriodElapsedCallback();
};
class Class_Gimbal
{
public:
    //变量
    Class_Yaw_Motor Yaw;
    //函数
    inline void Set_Target_Yaw_Angle(float __Target_Yaw_Angle);
    inline float Get_Target_Yaw_Angle();
    inline void Set_Gimbal_Status(Enum_Gimbal_Status _gimbal_status);
    void Init();
    void TIM_Gimbal_PeriodElapsedCallback();
protected:
    //变量
    Enum_Gimbal_Status gimbal_status;
    float Target_Yaw_Angle;
    //函数
    void OutPut();
};
#define  YAW_GEAR_RATIO  (72.f/1052.f)

void Class_Yaw_Motor::Set_Yaw_Target_Angle(float _Yaw_Target_Angle)
{
    Yaw_Target_Angle = _Yaw_Target_Angle;
}
void Class_Gimbal::Set_Target_Yaw_Angle(float __Target_Yaw_Angle)
{
    Target_Yaw_Angle = __Target_Yaw_Angle;
}
float Class_Gimbal::Get_Target_Yaw_Angle()
{
    return (Target_Yaw_Angle);
}
void Class_Gimbal::Set_Gimbal_Status(Enum_Gimbal_Status _gimbal_status)
{
    gimbal_status = _gimbal_status;
}
#endif
#endif
