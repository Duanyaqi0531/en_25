#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H
#include "stm32f1xx_hal.h"
//�洢����ʼ��ַ
#define STORE_START_ADDRESS		0x0800FC00
//�洢���ݵĸ���
#define STORE_COUNT				10000
extern uint16_t Store_Data[];

void Store_Init(void);
void Store_Save(void);
void Store_Clear(void);

#endif
