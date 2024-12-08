#include "crt_gimbal.h"
void Class_Yaw_Motor::TIM_PID_PeriodElapsedCallback()
{
    switch (DJI_Motor_Control_Method)
    {
    case (DJI_Motor_Control_Method_OPENLOOP):
    {
        //默认开环速度控制
        Out = Target_Torque / Omega_Max * Output_Max;
    }
    break;
    case (DJI_Motor_Control_Method_ANGLE):
    {
        PID_Angle.Set_Target(Yaw_Target_Encoder);
        PID_Angle.Set_Now(Data.Now_Angle/360*8192);
        PID_Angle.TIM_Adjust_PeriodElapsedCallback();

        Target_Omega_Rpm = PID_Angle.Get_Out();

        PID_Omega.Set_Target(Target_Omega_Rpm);
        PID_Omega.Set_Now(Data.Now_Omega_Rpm);
        PID_Omega.TIM_Adjust_PeriodElapsedCallback();

//        Target_Torque = PID_Omega.Get_Out();

//        PID_Torque.Set_Target(Target_Torque);
//        PID_Torque.Set_Now(Data.Now_Torque);
//        PID_Torque.TIM_Adjust_PeriodElapsedCallback();

        Out = PID_Omega.Get_Out();
    }
    break;
    default:
    {
        Out = 0.0f;
    }
    break;
    }
    Output();
}
void Class_Yaw_Motor::Yaw_Target_Angle_To_Encoder()
{
    Yaw_Target_Encoder = Yaw_Target_Angle/360*8191/YAW_GEAR_RATIO;
}
void Class_Yaw_Motor::Calculate_Yaw_Now_Angle()
{
    Yaw_Now_Angle = Get_Now_Angle()*YAW_GEAR_RATIO;
}
void Class_Gimbal::Init()
{
    gimbal_status = Gimbal_Disable;
    //yaw初始化
    Yaw.Init(&hcan2,DJI_Motor_ID_0x205,DJI_Motor_Control_Method_IMU_ANGLE);
    Yaw.PID_Angle.Init(8.0f,0.0f,0.0f,0.0f,2000.0f,16500,0.0f,0.0f,0.0f,0.001f);
    Yaw.PID_Omega.Init(25.0f,0.05f,0.0f,0.0f,2000.0f,5000,0.0f,0.0f,0.0f,0.001f);

}
void Class_Gimbal::OutPut()
{
    switch (gimbal_status)
    {
    case Gimbal_Disable:
        Yaw.yaw_status = Yaw_Disable;
        Yaw.Set_DJI_Motor_Control_Method(DJI_Motor_Control_Method_OPENLOOP);
        Yaw.Set_Target_Torque(0.0f);
        break;
    case Gimbal_Enable:
        Yaw.yaw_status = Yaw_Enable;
        Yaw.Set_DJI_Motor_Control_Method(DJI_Motor_Control_Method_ANGLE);
        //set_yaw_target_angle
        Yaw.Set_Yaw_Target_Angle(Target_Yaw_Angle);
        //计算目标编码器值
        Yaw.Yaw_Target_Angle_To_Encoder();
        break;
    default:
        break;
    }
}
void Class_Gimbal::TIM_Gimbal_PeriodElapsedCallback()
{
    //时实获取yaw实际角度
    Yaw.Calculate_Yaw_Now_Angle();

    OutPut();
    Yaw.TIM_PID_PeriodElapsedCallback();
}