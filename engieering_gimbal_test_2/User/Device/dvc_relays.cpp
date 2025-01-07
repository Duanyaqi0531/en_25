#include "dvc_relays.h"
// /* Private macros ------------------------------------------------------------*/

// /* Private types -------------------------------------------------------------*/

// /* Private variables ---------------------------------------------------------*/

// /* Private function declarations ---------------------------------------------*/

// /* Function prototypes -------------------------------------------------------*/

// /**
//  * @brief 初始化
//  * 
//  * @param __Driver_PWM_TIM 舵机驱动定时器编号
//  * @param __Driver_PWM_TIM_Channel_x 定时器通道

//  */
 void Class_Relays::Init(GPIO_TypeDef* __Driver_GPIOX, uint16_t __Driver_GPIO_Pin)
 {
     Driver_GPIOX = __Driver_GPIOX;
     Driver_GPIO_Pin = __Driver_GPIO_Pin;

 }

// /**
//  * @brief 角度输出
//  * 
//  */
 void Class_Relays::Output()
 {
	if(Target_State)
     HAL_GPIO_WritePin(Driver_GPIOX,Driver_GPIO_Pin,GPIO_PIN_SET);
	else 
	HAL_GPIO_WritePin(Driver_GPIOX,Driver_GPIO_Pin,GPIO_PIN_RESET);
 }
 /* Exported variables --------------------------------------------------------*/

 /* Exported function declarations --------------------------------------------*/

 /**
  * @brief 设定目标值
  * 
  * @param __Target_Angle 舵机角度目标值
  */
 void Class_Relays::Set_Target_State(Enum_Relays_Control_State __Target_State)
 {
     Target_State = __Target_State;
     Output();
 }
// /************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
