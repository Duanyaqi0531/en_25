#ifndef _CRT_BOSSTER_H_
#define _CRT_BOSSTER_H_
#ifdef __cplusplus
#include "dvc_djimotor.h"
#include "alg_fsm.h"
enum Enum_Booster_Status
{
    Booster_Disable,
    Booster_Enable,
};
enum Enum_Booster_Control_Type
{
    Booster_Control_Ceasefire,
    Booster_Control_Single,
};
enum Enum_Fric_Status
{
    Fric_Disable,
    Fric_Enable,
};
enum Enum_Push_Status
{
    Push_Disable,
    Push_Enable,
};
enum Enum_Push_Move_Type
{
    Push_Stop,
    Push_Forward,
    Push_Backward,
};
class Class_Fric_Motor : public Class_DJI_Motor_C620
{
public:
    //变量
    Enum_Fric_Status fric_status;
    //函数
    void TIM_PID_PeriodElapsedCallback();
};
class Class_Push_Motor : public Class_DJI_Motor_C610
{
public:
    //变量
    Enum_Push_Status push_status;
    Enum_Push_Move_Type push_move_type;
    float Push_Target_length;
    float Push_Now_Length;
    //内部函数
    void Calculate_Push_Length();
    void TIM_PID_PeriodElapsedCallback();
};
class Class_Booster
{
public:
    Class_Fric_Motor Fric_Motor[4];
    Class_Push_Motor Push_Motor;
    Class_FSM booster_fsm;
    uint8_t cnt;
    inline void Set_Booster_Status(Enum_Booster_Status _booster_status);
    inline void Set_Booster_Control_Type(Enum_Booster_Control_Type _booster_control_type);
    void Init();
    void TIM_Booster_PeriodElapsedCallback();
protected:
    //变量：
    int16_t Fric_Speed_High;//rpm
    int16_t Fric_Speed_Low;//rpm
    Enum_Booster_Status booster_status;
    Enum_Booster_Control_Type booster_control_type;
    //内部函数：
    void OutPut();
};
#define PUSH_ROUND_TO_LENGTH    8e-3f       //输出轴一圈对应的丝杆行程 单位m
#define PUSH_MOTOR_SPEED         8500       //push电机的转速 rpm
#define PUSH_MOTOR_STOP         0           //push电机的停止转速 rpm
void Class_Booster::Set_Booster_Status(Enum_Booster_Status _booster_status)
{
    booster_status = _booster_status;
}
void Class_Booster::Set_Booster_Control_Type(Enum_Booster_Control_Type _booster_control_type)
{
    booster_control_type = _booster_control_type;
}
#define push_length_1 0.16
#define push_length_2 0.32
#define push_length_3 0.48
#define push_length_4 0.58
#endif
#endif
