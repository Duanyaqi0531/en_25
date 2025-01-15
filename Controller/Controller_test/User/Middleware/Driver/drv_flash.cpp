#include "drv_flash.h"


uint32_t FLASH_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

  //FLASH读取一个16位的字
uint16_t FLASH_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

  //FLASH读取一个8位的字
uint8_t FLASH_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t *)(Address));	//使用指针访问指定地址下的数据并返回
}
void FLASH_ErasePage(uint32_t ErasePageBaseAddr,uint32_t ErasePageNbPageCount)
{
       HAL_FLASH_Unlock();
       FLASH_EraseInitTypeDef EraseInitStruct = {
           .TypeErase = FLASH_TYPEERASE_PAGES,       //页擦除
           .PageAddress = ErasePageBaseAddr,                //擦除地址
           .NbPages = ErasePageNbPageCount                             //擦除页数
       };
       uint32_t PageError = 0;
       __disable_irq();                             //擦除前关闭中断
       if (HAL_FLASHEx_Erase(&EraseInitStruct,&PageError) == HAL_OK)
       {
         //  printf("擦除 成功\r\n");
       }
       __enable_irq();
	   HAL_FLASH_Lock();					//加锁
}
//定义SRAM数组
uint16_t Store_Data[STORE_COUNT];	
//初始化假如没初始化过就初始化(第一个半字写特殊标志位0xA5A5，其余写入0)，假如初始化过就把闪存数据读取到数组Store_Data中
void Store_Init(void)
{
	/*判断是不是第一次使用*/
	if (FLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)	//读取第一个半字的标志位，if成立，则执行第一次使用的初始化
	{
		FLASH_ErasePage(STORE_START_ADDRESS,1);					//擦除指定页
		HAL_FLASH_Unlock();

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS,0xA5A5);//在第一个半字写入自己规定的标志位，用于判断是不是第一次使用
		for (uint16_t i = 1; i < STORE_COUNT; i ++)				//循环STORE_COUNT次，除了第一个标志位
		{
	
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS + i * 2,0x0000);//除了标志位的有效数据全部清0
		}
		HAL_FLASH_Lock();
	}
	
	/*上电时，将闪存数据加载回SRAM数组，实现SRAM数组的掉电不丢失*/
	for (uint16_t i = 0; i < STORE_COUNT; i ++)					//循环STORE_COUNT次，包括第一个标志位
	{
		Store_Data[i] = FLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);		//将闪存的数据加载回SRAM数组
	}
}
//数组保存到闪存
void Store_Save(void)
{
	FLASH_ErasePage(STORE_START_ADDRESS,1);				//擦除指定页
	HAL_FLASH_Unlock();
	for (uint16_t i = 0; i < STORE_COUNT; i ++)			//循环STORE_COUNT次，包括第一个标志位
	{

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS + i * 2,Store_Data[i]);	//将SRAM数组的数据备份保存到闪存
	}
	HAL_FLASH_Lock();
}

void Store_Clear(void)
{
	for (uint16_t i = 1; i < STORE_COUNT; i ++)			//循环STORE_COUNT次，除了第一个标志位
	{
		Store_Data[i] = 0x0000;							//SRAM数组有效数据清0
	}
	Store_Save();										//保存数据到闪存
}
