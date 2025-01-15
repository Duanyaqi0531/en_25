#include "drv_flash.h"


uint32_t FLASH_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t *)(Address));	//ʹ��ָ�����ָ����ַ�µ����ݲ�����
}

  //FLASH��ȡһ��16λ����
uint16_t FLASH_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t *)(Address));	//ʹ��ָ�����ָ����ַ�µ����ݲ�����
}

  //FLASH��ȡһ��8λ����
uint8_t FLASH_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t *)(Address));	//ʹ��ָ�����ָ����ַ�µ����ݲ�����
}
void FLASH_ErasePage(uint32_t ErasePageBaseAddr,uint32_t ErasePageNbPageCount)
{
       HAL_FLASH_Unlock();
       FLASH_EraseInitTypeDef EraseInitStruct = {
           .TypeErase = FLASH_TYPEERASE_PAGES,       //ҳ����
           .PageAddress = ErasePageBaseAddr,                //������ַ
           .NbPages = ErasePageNbPageCount                             //����ҳ��
       };
       uint32_t PageError = 0;
       __disable_irq();                             //����ǰ�ر��ж�
       if (HAL_FLASHEx_Erase(&EraseInitStruct,&PageError) == HAL_OK)
       {
         //  printf("���� �ɹ�\r\n");
       }
       __enable_irq();
	   HAL_FLASH_Lock();					//����
}
//����SRAM����
uint16_t Store_Data[STORE_COUNT];	
//��ʼ������û��ʼ�����ͳ�ʼ��(��һ������д�����־λ0xA5A5������д��0)�������ʼ�����Ͱ��������ݶ�ȡ������Store_Data��
void Store_Init(void)
{
	/*�ж��ǲ��ǵ�һ��ʹ��*/
	if (FLASH_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)	//��ȡ��һ�����ֵı�־λ��if��������ִ�е�һ��ʹ�õĳ�ʼ��
	{
		FLASH_ErasePage(STORE_START_ADDRESS,1);					//����ָ��ҳ
		HAL_FLASH_Unlock();

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS,0xA5A5);//�ڵ�һ������д���Լ��涨�ı�־λ�������ж��ǲ��ǵ�һ��ʹ��
		for (uint16_t i = 1; i < STORE_COUNT; i ++)				//ѭ��STORE_COUNT�Σ����˵�һ����־λ
		{
	
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS + i * 2,0x0000);//���˱�־λ����Ч����ȫ����0
		}
		HAL_FLASH_Lock();
	}
	
	/*�ϵ�ʱ�����������ݼ��ػ�SRAM���飬ʵ��SRAM����ĵ��粻��ʧ*/
	for (uint16_t i = 0; i < STORE_COUNT; i ++)					//ѭ��STORE_COUNT�Σ�������һ����־λ
	{
		Store_Data[i] = FLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);		//����������ݼ��ػ�SRAM����
	}
}
//���鱣�浽����
void Store_Save(void)
{
	FLASH_ErasePage(STORE_START_ADDRESS,1);				//����ָ��ҳ
	HAL_FLASH_Unlock();
	for (uint16_t i = 0; i < STORE_COUNT; i ++)			//ѭ��STORE_COUNT�Σ�������һ����־λ
	{

		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,STORE_START_ADDRESS + i * 2,Store_Data[i]);	//��SRAM��������ݱ��ݱ��浽����
	}
	HAL_FLASH_Lock();
}

void Store_Clear(void)
{
	for (uint16_t i = 1; i < STORE_COUNT; i ++)			//ѭ��STORE_COUNT�Σ����˵�һ����־λ
	{
		Store_Data[i] = 0x0000;							//SRAM������Ч������0
	}
	Store_Save();										//�������ݵ�����
}
