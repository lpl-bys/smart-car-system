#ifndef _PIDYAW_H
#define _PIDYAW_H


#include "system.h"
#include "pid.h"
#include "servo.h"
#include "JY901.h"


#define YAWPID_TIM_PORT_RCC		RCC_APB1Periph_TIM2
#define YAWPID_TIM						TIM2


extern PID_Calibration 	yaw_pid_calibration;
extern PID_State				yaw_pid_state;	

extern float KP1,KI1,KD1;

void yawPID_Init(void);	
void YAWPIDscan_Init(void);
void PID_changeAngle(u8 angle);





#endif
