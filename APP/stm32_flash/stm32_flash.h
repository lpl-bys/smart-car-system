#ifndef _stm32_flash_H
#define _stm32_flash_H

#include "system.h"


//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 128 	 //��ѡSTM32��FLASH������С(��λΪK)

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ 

#define STM32_FLASH_SAVE_ADDR  0X08018800		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)


//#define KP1_SAVE_ADDR					0X08018800
//#define KI1_SAVE_ADDR					0X08018802
#define SPEED_HPER_SAVE_ADDR	0X08018804
#define SPEED_LPER_SAVE_ADDR	0X08018806
#define KP1_SAVE_ADDR					0X08018808
#define KI1_SAVE_ADDR					0X0801880A
#define KD1_SAVE_ADDR					0X0801880C



 
vu16 STM32_FLASH_ReadHalfWord(u32 faddr); 
void STM32_FLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STM32_FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����
					   


#endif
