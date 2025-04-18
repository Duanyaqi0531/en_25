/**
 * @file tsk_config_and_callback.cpp
 * @author yssickjgd (yssickjgd@mail.ustc.edu.cn)
 * @brief 临时任务调度测试用函数, 后续用来存放个人定义的回调函数以及若干任务
 * @version 0.1
 * @date 2023-08-29 0.1 23赛季定稿
 *
 * @copyright USTC-RoboWalker (c) 2022
 *
 */

/**
 * @brief TIM开头的默认任务均1ms, 特殊任务需额外标记时间
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "tsk_config_and_callback.h"
#include "dvc_encoder.h"
#include "drv_flash.h"
#include "drv_tim.h"
#include "drv_uart.h"
#include "dvc_referee.h"
#include "RoboTram.h"
#include "tim.h"
#include "main.h"
/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//Class_Encoder Encoder[5];
Class_RobotTram RobotTram;


/* Private function declarations ---------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/


/**
* @brief 前四个编码器接收回调函数
*
* @param Buffer UART收到的消息
* @param Length 长度
*/
// #ifdef Encoder_B
// void Encoder_UART2_Callback(uint8_t *Buffer, uint16_t Length)
// {
//   if(Buffer[0]==0xA5 && Buffer[13]==0x11 && Length==14)
//   {
//     for(auto i=0;i<4;i++)
//     {
//       uint16_t IntAngle;
//       int8_t total_round;
//       memcpy(&IntAngle,&Buffer[3*i+1],2);
//       memcpy(&total_round,&Buffer[3*i+3],1);
//       Encoder[i].Set_Now_Angle((float)IntAngle/100.0f);
//       Encoder[i].Set_Total_Round((int16_t)total_round);
//     }
//   }
// }
// #endif
/**
* @brief UART裁判系统回调函数
*RobotTram
* @param Buffer UART收到的消息
* @param Length 长度
*/
void Referee_UART3_Callback(uint8_t *Buffer, uint16_t Length)
{
  RobotTram.Referee.UART_RxCpltCallback(Buffer);
}
/**************************************************************************
  * @brief  ????????
  * @retval 
**************************************************************************/
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//	__HAL_UNLOCK(huart);
//    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET)
//    {
//		__HAL_UART_CLEAR_PEFLAG(huart);
//    }
//    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET)
//    {
//		__HAL_UART_CLEAR_FEFLAG(huart);
//		if(huart->Instance == USART1)
//		{
//			UART_Init(&huart1,OpticalFlow_UART1_Callback,70);
//		}
//		else if(huart->Instance == USART2)
//		{
//			UART_Init(&huart2,Referee_UART2_Callback,128);
//		}
//		
//    }
//    
//    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET)
//    {
//		__HAL_UART_CLEAR_NEFLAG(huart);
//		if(huart->Instance == USART1)
//		{
//			UART_Init(&huart1,OpticalFlow_UART1_Callback,70);
//		}
//		else if(huart->Instance == USART2)
//		{
//			UART_Init(&huart2,Referee_UART2_Callback,128);
//		}
//    }       
//    
//    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET)
//    {
//		__HAL_UART_CLEAR_OREFLAG(huart);
//    }    
// 
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  RobotTram.Encoder[4].GPIO_EXIT_Encoder_Updata(GPIO_Pin);
}

void Encoder_Data_Control_Trasmit()
{
  uint8_t tmp_data[17];
  tmp_data[0] = 0xA5;
  for(auto i=0;i<5;i++)
  {
    int16_t IntAngle;
    int8_t total_round;
    IntAngle = (int16_t)(RobotTram.Encoder[i].Get_Now_Angle()*100);
    total_round = (int8_t)RobotTram.Encoder[i].Get_Total_Round();
    memcpy(&tmp_data[3*i+1],&IntAngle,2);
    memcpy(&tmp_data[3*i+3],&total_round,1);
  }
  tmp_data[16] = 0x11;
  HAL_UART_Transmit(&huart3,tmp_data,17,10);
}


void Task_Init()
{

  RobotTram.Init();
	RobotTram.Referee.Init(&huart3);
	// TIM_Init(&htim6, Task1ms_TIM6_Callback);



}
GPIO_PinState get_key_temp;
void Task_loop()
{
  // //五个编码器角度计算

  RobotTram.Calculate_RobotTram_Angle();
	get_key_temp=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
	
	if(get_key_temp==1)
	{
	RobotTram.key_flag=1;
	}
	else 
	{
	RobotTram.key_flag=0;
	}
 // RobotTram.RoboTram_Angle_Control_Trasmit();

		HAL_Delay(33);
  //裁判系统打包发送所有的编码器角度
  RobotTram.Encoder_Data_Referee_Trasmit();
  //直接给机器发送所有的编码器角度
   //Encoder_Data_Control_Trasmit();
}


/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
