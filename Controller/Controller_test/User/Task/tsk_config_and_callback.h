/**
 * @file tsk_config_and_callback.h
 * @author yssickjgd (yssickjgd@mail.ustc.edu.cn)
 * @brief
 * @version 0.1
 * @date 2023-08-29 0.1 23赛季定稿
 *
 * @copyright USTC-RoboWalker (c) 2022
 *
 */
#ifndef TSK_CONFIG_AND_CALLBACK_H
#define TSK_CONFIG_AND_CALLBACK_H


/* Includes ------------------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/



#ifdef __cplusplus
extern "C"
{
#endif
 
  void Task_Init();
  void Task_loop();
  void Encoder_Data_Referee_Trasmit();
  void Encoder_Data_Control_Trasmit();
 
#ifdef __cplusplus
}
#endif

#endif
/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/
