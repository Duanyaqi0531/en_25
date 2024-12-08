#include "dvc_encoder.h"



void Class_Encoder::Init(TIM_HandleTypeDef *__TIM_EncoderHandle,  uint16_t __encoder_resolution, uint32_t __max_encoder_sum)
{
    //定时器编码器外设初始化
    HAL_TIM_Encoder_Start(__TIM_EncoderHandle,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(__TIM_EncoderHandle,TIM_CHANNEL_2);

    TIM_EncoderHandle = __TIM_EncoderHandle;
    Max_Encoder_Sum = __max_encoder_sum;
    Encoder_Resolution = __encoder_resolution;

    Now_Encoder = 0;
    //上次脉冲值
    Last_Encoder = 0;
    //脉冲差值
    Encoder_Diff = 0;
    //脉冲累加和 ±
    Encoder_Diff_Sum = 0;
    //当前圈数
    Total_Round = 0;    
    //当前角度
    Now_Angle = 0;
    //总角度
    Total_Angle = 0;	
}


void Class_Encoder::Init(GPIO_TypeDef* __GPIOx, uint16_t __GPIO_Pin_A, uint16_t __GPIO_Pin_B)
{
    //GPIO编码器外设初始化
    GPIOx = __GPIOx;
    GPIO_Pin_A = __GPIO_Pin_A;
    GPIO_Pin_B = __GPIO_Pin_B;

    Now_Encoder = 0;
    //上次脉冲值
    Last_Encoder = 0;
    //脉冲差值
    Encoder_Diff = 0;
    //脉冲累加和 ±
    Encoder_Diff_Sum = 0;    
    //当前圈数
    Total_Round = 0;    
    //当前角度
    Now_Angle = 0;
    //总角度
    Total_Angle = 0;	
}


void Class_Encoder::TIM_Encoder_Calculatye()
{
    //获取当前脉冲值
    Now_Encoder = TIM_EncoderHandle->Instance->CNT;
    //计算脉冲差值
    Encoder_Diff = (int32_t)(Now_Encoder - Last_Encoder);
    //更新上次编码器值
    Last_Encoder = Now_Encoder;

    if(Encoder_Diff > Max_Encoder_Sum/2)
    {
        Encoder_Diff = Encoder_Diff - Max_Encoder_Sum;
    }
    else if(Encoder_Diff < -(int32_t)Max_Encoder_Sum/2)
    {
        Encoder_Diff = Encoder_Diff + Max_Encoder_Sum;
    }

    //模拟单圈编码器 0-Encoder_Resolution 计算圈数
    Encoder_Diff_Sum += Encoder_Diff;
    if(Encoder_Diff_Sum > (int32_t)Encoder_Resolution)
    {
        Encoder_Diff_Sum -= (int32_t)Encoder_Resolution;
        Total_Round++;
    }
    else if(Encoder_Diff_Sum < 0)
    {
        Encoder_Diff_Sum += (int32_t)Encoder_Resolution;
        Total_Round--;
    }
  //计算角度
    Now_Angle = (float)Encoder_Diff_Sum/(int32_t)Encoder_Resolution*360.0f;
    Total_Angle = (float)(Encoder_Diff_Sum + Total_Round*(int32_t)Encoder_Resolution)/(int32_t)Encoder_Resolution*360.0f;
}

void Class_Encoder::GPIO_Encoder_Calculatye()
{
    //模拟单圈编码器 0-Encoder_Resolution 计算圈数
    if(Encoder_Diff_Sum > (int32_t)Encoder_Resolution)
    {
        Encoder_Diff_Sum -= (int32_t)Encoder_Resolution;
        Total_Round++;
    }
    else if(Encoder_Diff_Sum < 0)
    {
        Encoder_Diff_Sum += (int32_t)Encoder_Resolution;
        Total_Round--;
    }
    //计算角度
    Now_Angle = (float)Encoder_Diff_Sum/(int32_t)Encoder_Resolution*360.0f;
    Total_Angle = (float)(Encoder_Diff_Sum + Total_Round*(int32_t)Encoder_Resolution)/(int32_t)Encoder_Resolution*360.0f;    
}

void Class_Encoder::GPIO_EXIT_Encoder_Updata(uint16_t __GPIO_Pin_x)
{
static uint8_t Encoder_Status = 1;
  if(__GPIO_Pin_x == GPIO_Pin_A)
  {
    if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_A) == GPIO_PIN_SET)//A相上升沿
    {
      if(Encoder_Status == 2)
      {
        Encoder_Status = 1;
        Encoder_Diff_Sum--;
      }
      else if(Encoder_Status == 3)
      {
        Encoder_Status = 4;
        Encoder_Diff_Sum++;
      }
    }
    else if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_A) == GPIO_PIN_RESET)//A相下降沿
    {
      if(Encoder_Status == 1)
      {
        Encoder_Status = 2;
        Encoder_Diff_Sum++;
      }
      else if(Encoder_Status == 4)
      {
        Encoder_Status = 3;
        Encoder_Diff_Sum--;
      }
    }
  }
  else if(__GPIO_Pin_x == GPIO_Pin_B)
  {
    if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_B) == GPIO_PIN_SET)//B相上升沿
    {
      if(Encoder_Status == 1)
      {
        Encoder_Status = 4;
        Encoder_Diff_Sum--;
      }
      else if(Encoder_Status == 2)
      {
        Encoder_Status = 3;
        Encoder_Diff_Sum++;
      }
    }
    else if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin_B) == GPIO_PIN_RESET)//B相下降沿
    {
      if(Encoder_Status == 3)
      {
        Encoder_Status = 2;
        Encoder_Diff_Sum--;
      }
      else if(Encoder_Status == 4)
      {
        Encoder_Status = 1;
        Encoder_Diff_Sum++;
      }
    }
  }    
}