#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "stm32f1xx_hal.h"
#include "string.h"

#ifdef __cplusplus

class Class_Encoder
{
    public:
    void Init(TIM_HandleTypeDef *__TIM_EncoderHandle,  uint16_t __encoder_resolution = 4096, uint32_t __max_encoder_sum = 65535); 
    void Init(GPIO_TypeDef* __GPIOx, uint16_t __GPIO_Pin_A, uint16_t __GPIO_Pin_B);
    void TIM_Encoder_Calculatye();
    void GPIO_Encoder_Calculatye();

    void GPIO_EXIT_Encoder_Updata(uint16_t __GPIO_Pin_x);

    inline float Get_Now_Angle();
    inline int16_t Get_Total_Round();
    inline float Get_Total_Angle();

    inline void Set_Now_Angle(float __angle);
    inline void Set_Total_Round(int16_t __round);
    inline void Set_Encoder_Diff_Sum(int32_t __diff_sum);

    protected:

    //编码器外设句柄
    TIM_HandleTypeDef * TIM_EncoderHandle;
    //编码器最大值 65535
    uint16_t Max_Encoder_Sum;
    //编码器分辨率 一圈多少个脉冲
    uint32_t Encoder_Resolution = 4096;

    //GPIO外设端口
    GPIO_TypeDef* GPIOx;
    //A相引脚
    uint16_t GPIO_Pin_A;
    //B相引脚
    uint16_t GPIO_Pin_B;

    //当前脉冲值
    int32_t Now_Encoder;
    //上次脉冲值
    int32_t Last_Encoder;
		//脉冲累加和 ±
    int32_t Encoder_Diff_Sum;
    //脉冲差值
    int32_t Encoder_Diff;
    //当前圈数
    int16_t Total_Round;
    //当前角度
    float Now_Angle;
    //总角度
    double Total_Angle;
};


void Encoder_Transimit(UART_HandleTypeDef * __huart,Class_Encoder Encoder[4]);


float Class_Encoder::Get_Now_Angle()
{
    return (Now_Angle);
}

int16_t Class_Encoder::Get_Total_Round()
{
    return (Total_Round);
}

float Class_Encoder::Get_Total_Angle()
{
    return (Total_Angle);
}

void Class_Encoder::Set_Now_Angle(float __angle)
{
    Now_Angle = __angle;
}

void Class_Encoder::Set_Total_Round(int16_t __round)
{
    Total_Round = __round;
}

void Class_Encoder::Set_Encoder_Diff_Sum(int32_t __diff_sum)
{
    Encoder_Diff_Sum = __diff_sum;
}

#endif

#endif


