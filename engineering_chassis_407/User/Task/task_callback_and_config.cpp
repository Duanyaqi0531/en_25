#include "task_callback_and_config.h"
#include "ita_chariot.h"
#include "drv_tim.h"
#include "drv_can.h"
Class_Chariot chariot;
uint32_t init_finished = 0;
uint8_t start_flag = 0;
uint32_t Alive_flag;
uint32_t Pre_Alive_flag;
uint8_t Stop[8]={0,0,0,0,0,0,0,0};
void Chariot_Device_CAN1_Callback(Struct_CAN_Rx_Buffer *CAN_RxMessage)
{
    switch (CAN_RxMessage->Header.StdId)
    {
    case (0x201):
    {
        chariot.chassis.Motor_Wheel[0].CAN_RxCpltCallback(CAN_RxMessage->Data);
    }
    break;
    case (0x202):
    {
        chariot.chassis.Motor_Wheel[1].CAN_RxCpltCallback(CAN_RxMessage->Data);
    }
    break;
    case (0x203):
    {
        chariot.chassis.Motor_Wheel[2].CAN_RxCpltCallback(CAN_RxMessage->Data);
    }
    break;
    case (0x204):
    {
        chariot.chassis.Motor_Wheel[3].CAN_RxCpltCallback(CAN_RxMessage->Data);
    }
    break;
    }
}
void Chariot_Device_CAN2_Callback(Struct_CAN_Rx_Buffer *CAN_RxMessage)
{
    switch (CAN_RxMessage->Header.StdId)
    {
    case (0x205):
    {
        
    }
    case (0x088):
    {
        chariot.CAN_Chassis_Rx_Gimbal_Callback();
			Alive_flag++;
			
    }
    break;
    break;
    }
}
void Class_Chariot::TIM1msMod50_Alive_PeriodElapsedCallback()
{
        for (auto i = 0; i < 4; i++)
        {
            chassis.Motor_Wheel[i].TIM_Alive_PeriodElapsedCallback();
        }
        TIM1msMod50_Gimbal_Communicate_Alive_PeriodElapsedCallback();
				if(chariot.Gimbal_Status == Gimbal_Status_DISABLE)
				{
					chariot.chassis.Set_Chassis_Control_Type(Chassis_Control_Type_DISABLE);
				}
}

float Motor_Target_Speed;
uint8_t mod50_cnt = 0;
void Task1ms_TIM5_Callback()
{
    init_finished++;
		mod50_cnt++;
    if(init_finished>2000)
    start_flag=1;
		if(mod50_cnt%50==0)
		{
		 chariot.TIM1msMod50_Alive_PeriodElapsedCallback();
		 mod50_cnt = 0;
		}
		chariot.TIM_Chariot_PeriodElapsedCallback();
	TIM_CAN_PeriodElapsedCallback();
}
extern "C" void Task_Init()
{
    //can总线
    CAN_Init(&hcan1,Chariot_Device_CAN1_Callback);
    CAN_Init(&hcan2,Chariot_Device_CAN2_Callback);
    //定时器循环任务
    TIM_Init(&htim5,Task1ms_TIM5_Callback);
    //交互层
    chariot.Init();
	
		HAL_TIM_Base_Start_IT(&htim5);
	
}