#ifndef _ACTION_H
#define _ACTION_H

#include "system.h" 
#include "SysTick.h"

#define QDCOM_PORT				GPIOB
#define QDCOM_PORT_RCC		RCC_APB2Periph_GPIOB
#define ENA_PIN						GPIO_Pin_10
#define ENB_PIN						GPIO_Pin_11
#define IN1_PIN						GPIO_Pin_5
#define IN2_PIN						GPIO_Pin_6
#define IN3_PIN						GPIO_Pin_7
#define IN4_PIN						GPIO_Pin_8


void actionInit(void);
void goStraight(u8 speed);









#endif
