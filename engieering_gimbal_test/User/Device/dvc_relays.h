#include "stm32f4xx_hal.h"
enum Enum_Relays_Control_State
{
    Relays_Control_State_DISABLE = 0,
    Relays_Control_State_ENABLE,
};
class Class_Relays
{
	public:
 void Init(GPIO_TypeDef* GPIOX, uint16_t __Driver_GPIO_Pin);
 void Set_Target_State(Enum_Relays_Control_State __Target_State);
 protected:
     //初始化相关常量

     //驱动定时器编号
     GPIO_TypeDef *Driver_GPIOX;
     //定时器通道
     uint8_t Driver_GPIO_Pin;
     //常量

     //内部变量

     //读变量

     //写变量

     //读写变量
		Enum_Relays_Control_State Target_State;
     //内部函数
    
     void Output();
 };


