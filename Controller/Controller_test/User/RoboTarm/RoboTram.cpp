#include "RoboTram.h"
#include "tim.h"
#include "usart.h"
#include "tsk_config_and_callback.h"
void Class_RobotTram::Init()
{
    Encoder[0].Init(&htim1);
    Encoder[1].Init(&htim2);
    Encoder[2].Init(&htim3);
    Encoder[3].Init(&htim4);
    Encoder[4].Init(&htim5);

}

void Class_RobotTram::Calculate_RobotTram_Angle()
{
    for(auto i=0;i<5;i++)
    {
        Encoder[i].TIM_Encoder_Calculatye();
        Angle[i] = -1.f*Encoder[i].Get_Total_Angle() + Angle_Offset[i];
			
    }
				Angle[4]= Angle[4]*2;
				Angle[3]= Angle[3]*2;
}
uint8_t tmp_data[12];
void Class_RobotTram::RoboTram_Angle_Control_Trasmit()
{
    
    tmp_data[0] = 0xA5;
    for(auto i=0;i<5;i++)
    {
        int16_t IntAngle;
        IntAngle = (int16_t)(Angle[i]*100);
        memcpy(&tmp_data[2*i+1],&IntAngle,2);
    }
    tmp_data[11] = 0x11;
    HAL_UART_Transmit(&huart3,tmp_data,12,10);
}