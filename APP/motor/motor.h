#ifndef _MOTOR_H
#define _MOTOR_H

#include "system.h"

#define MOTOR_PORT_RCC	RCC_APB2Periph_GPIOB
#define MOTOR_PORT			GPIOB

#define MOTOR_ENA_PIN		GPIO_Pin_12
#define MOTOR_ENB_PIN		GPIO_Pin_13

#define MOTOR_IN1_PIN		GPIO_Pin_7
#define MOTOR_IN2_PIN		GPIO_Pin_8
#define MOTOR_IN3_PIN		GPIO_Pin_14
#define MOTOR_IN4_PIN		GPIO_Pin_15

#define GO_FORWARD	0x01
#define GO_BACKWARD	0x02
#define BRAKE				0x03
//#define STOP				0x00

#define SPEED_LEVEL_0 0x00
#define SPEED_LEVEL_1	0x01
#define SPEED_LEVEL_2	0x02
#define SPEED_LEVEL_3	0x03
#define SPEED_LEVEL_4	0x04
#define SPEED_LEVEL_5	0x05

extern u8 car_speed;

void motorInit(void);
void controlMotor(u8 direction);
void controlSpeed(void);




#endif
