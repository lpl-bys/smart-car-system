#ifndef _dma_H
#define _dma_H

#include "system.h"
#include "LED.h"
#include "SysTick.h"
#include "usart.h"
#include "ESP8266.h"
#include "public.h"
#include <string.h>

//DMA接管USART串口
#define DMA1_USARTX_BUFF_SIZE		2333

//#define DMA1_USART1							USART1
//#define DMA1_USART2							USART2
#define DMA1_USART3							USART3

#define DMA1_USARTX							DMA1_USART3

#ifdef DMA1_USART3
#define USARTX_ADDR							(u32)&USART3->DR
#define DMA1_USARTX_TX_CHANNELX	DMA1_Channel2
#define DMA1_USARTX_RX_CHANNELX	DMA1_Channel3
#define DMA1_USARTX_RX_FLAG_TCX	DMA1_FLAG_TC3
#define DMA1_USARTX_TX_FLAG_TCX	DMA1_FLAG_TC2
#endif

void DMA1_USARTX_Init(void);
void Send_Data(u32 datelen);
//void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx,u16 ndtr);	//使能一次DMA传输

#endif
