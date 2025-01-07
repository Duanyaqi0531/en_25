#include "dvc_relays.h"
// /* Private macros ------------------------------------------------------------*/

// /* Private types -------------------------------------------------------------*/

// /* Private variables ---------------------------------------------------------*/

// /* Private function declarations ---------------------------------------------*/

// /* Function prototypes -------------------------------------------------------*/

// /**
//  * @brief ��ʼ��
//  * 
//  * @param __Driver_PWM_TIM ���������ʱ�����
//  * @param __Driver_PWM_TIM_Channel_x ��ʱ��ͨ��

//  */
 void Class_Relays::Init(GPIO_TypeDef* __Driver_GPIOX, uint16_t __Driver_GPIO_Pin)
 {
     Driver_GPIOX = __Driver_GPIOX;
     Driver_GPIO_Pin = __Driver_GPIO_Pin;

 }

// /**
//  * @brief �Ƕ����
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
  * @brief �趨Ŀ��ֵ
  * 
  * @param __Target_Angle ����Ƕ�Ŀ��ֵ
  */
 void Class_Relays::Set_Target_State(Enum_Relays_Control_State __Target_State)
 {
     Target_State = __Target_State;
     Output();
 }
// /************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
