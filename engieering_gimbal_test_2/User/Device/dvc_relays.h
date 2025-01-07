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
     //��ʼ����س���

     //������ʱ�����
     GPIO_TypeDef *Driver_GPIOX;
     //��ʱ��ͨ��
     uint8_t Driver_GPIO_Pin;
     //����

     //�ڲ�����

     //������

     //д����

     //��д����
		Enum_Relays_Control_State Target_State;
     //�ڲ�����
    
     void Output();
 };


