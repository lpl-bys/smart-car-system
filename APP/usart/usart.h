#ifndef __usart_H
#define __usart_H

#include "system.h" 
#include "string.h"
#include "stdio.h" 


#define BRAKING 			'0'
#define GO_STRAIGHT		'1'
#define GO_BACK				'2'
#define TURN_LEFT			'3'
#define TURN_RIGHT		'4'

extern u16 YawTarget;


void USART1_Init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);
void UART2_Put_Char(unsigned char DataToSend);
void UART2_Put_String(unsigned char *Str);
void CopeSerial2Data(unsigned char ucData);
void CopeSerial1Data(unsigned char ucData);
void CopeSerial3Data(void);

#endif


