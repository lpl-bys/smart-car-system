#ifndef	_SERVO_H
#define	_SERVO_H

#include "system.h"

#define SERVO_PORT_RCC	RCC_APB2Periph_GPIOB
#define SERVO_PORT			GPIOB
#define SERVO_PIN				GPIO_Pin_1


void servoInit(void);
void toCenter(void);
void changeAngle(short angle);






#endif
