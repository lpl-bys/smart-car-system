#include "dma.h"

char send_buffer[DMA1_USARTX_BUFF_SIZE];
char receive_buffer[DMA1_USARTX_BUFF_SIZE];
extern u8 TAG_OK,TCP_CONTINUE,CUT_CONNECT_STATION;

/*******************************************************************************
* 函 数 名         : DMAx_Init
* 函数功能		   : DMA初始化函数
* 输    入         : 
					 DMAy_Channelx:DMA通道选择,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 par:外设地址
					 mar:存储器地址
					 ndtr:数据传输量
* 输    出         : 无
*******************************************************************************/ 
void DMA1_USARTX_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA1时钟使能 
	
	//DMA_DeInit(DMAy_Channelx);
	
	/* 配置 DMA TX*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USARTX_ADDR;//DMA外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)send_buffer;//DMA 存储器0地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//存储器到外设模式
	DMA_InitStructure.DMA_BufferSize = DMA1_USARTX_BUFF_SIZE;//数据传输量 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 使用普通模式 
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_USARTX_TX_CHANNELX, &DMA_InitStructure);//初始化DMA 
	
	/* 配置 DMA RX*/
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)receive_buffer;//DMA 存储器0地址
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_Init(DMA1_USARTX_RX_CHANNELX, &DMA_InitStructure);//初始化DMA 
	
	//USART_DMACmd(DMA1_USARTX,USART_DMAReq_Tx|USART_DMAReq_Rx,ENABLE);
	
	DMA_ClearFlag(DMA1_USARTX_RX_FLAG_TCX);
	DMA_ITConfig(DMA1_USARTX_RX_CHANNELX,DMA_IT_TE,ENABLE);
	DMA_Cmd(DMA1_USARTX_RX_CHANNELX,ENABLE);
}

/*******************************************************************************
* 函 数 名         : DMAx_Enable
* 函数功能		   : 开启一次DMA传输
* 输    入         : DMAy_Channelx:DMA通道选择,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
					 ndtr:数据传输量
* 输    出         : 无
*******************************************************************************/ 
//void DMAx_Enable(DMA_Channel_TypeDef *DMAy_Channelx,u16 ndtr)
//{
// 
//	DMA_Cmd(DMAy_Channelx, DISABLE);                      //关闭DMA传输 
//	
//	DMA_SetCurrDataCounter(DMAy_Channelx,ndtr);          //数据传输量  
// 
//	DMA_Cmd(DMAy_Channelx, ENABLE);                      //开启DMA传输 
//}	  

void USART3_IRQHandler(void){//空闲中断函数，通过串口DMA接收不定长数据后进入
	//u32 r,i;
//	u8 i;
//	char cx[9];
//	memset(cx,0,sizeof(cx));
//	strcpy(send_buffer,"ENTER\r\n");
//	Send_Data(7);
	if(USART_GetFlagStatus(DMA1_USARTX,USART_FLAG_IDLE)!=RESET){
		DMA_Cmd(DMA1_USARTX_RX_CHANNELX,DISABLE);
		DMA_ClearFlag( DMA1_USARTX_RX_FLAG_TCX );  
		DMA1_USARTX_RX_CHANNELX->CNDTR=DMA1_USARTX_BUFF_SIZE;
	//	r=DMA1_USARTX_BUFF_SIZE-DMA_GetCurrDataCounter(DMA1_USARTX_RX_CHANNELX);
		if(strstr(receive_buffer,"OK")) TAG_OK=1;
		if(strstr(receive_buffer,"CLOSED")||String_Compare(receive_buffer,"WIFI GOT IP",23,11))	TCP_CONTINUE=0;
//		if(strstr(receive_buffer,"ON-LED")) 		led3=0;
//		if(strstr(receive_buffer,"OFF-LED"))		led3=1;
		if(strstr(receive_buffer,"CUT"))				CUT_CONNECT_STATION=1;
		if(strstr(receive_buffer,"0,CONNECT"))	TCP_CONTINUE=1;
		
//		for(i=0;i<5;i++) cx[i]=receive_buffer[i];
		if(strstr(receive_buffer,"+IPD"))			CopeSerial3Data();
		
		memset(receive_buffer,0,sizeof(receive_buffer));

//		for(i=0;i<r;i++)
//			send_buffer[i]=receive_buffer[i];
		
		
//		DMA_Cmd(DMA1_USARTX_TX_CHANNELX, DISABLE);                      //关闭DMA传输 
//		DMA_SetCurrDataCounter(DMA1_USARTX_TX_CHANNELX,r);          //数据传输量  
//		DMA_Cmd(DMA1_USARTX_TX_CHANNELX, ENABLE);   
//		while(DMA_GetFlagStatus(DMA1_USARTX_TX_FLAG_TCX)!=SET);
//		DMA_ClearFlag(DMA1_USARTX_TX_FLAG_TCX);
		
		DMA_Cmd(DMA1_USARTX_RX_CHANNELX,ENABLE);
	}
	USART_ReceiveData(DMA1_USARTX);
	USART_ClearFlag(DMA1_USARTX,USART_FLAG_IDLE);
//	strcpy(send_buffer,"OUT\r\n");
//	Send_Data(5);
}

//数据传输量: datelen
void Send_Data(u32 datelen){
	DMA_Cmd(DMA1_USARTX_TX_CHANNELX, DISABLE);                      //关闭DMA传输 
	DMA_SetCurrDataCounter(DMA1_USARTX_TX_CHANNELX,datelen);          //数据传输量  
	DMA_Cmd(DMA1_USARTX_TX_CHANNELX, ENABLE);   
	while(DMA_GetFlagStatus(DMA1_USARTX_TX_FLAG_TCX)!=SET);
	DMA_ClearFlag(DMA1_USARTX_TX_FLAG_TCX);
	//DMA_Cmd(DMA1_USARTX_RX_CHANNELX,ENABLE);
}

