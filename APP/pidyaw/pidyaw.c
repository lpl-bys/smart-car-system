#include "pidyaw.h"
#include "public.h"
#include "stm32_flash.h"



PID_Calibration yaw_pid_calibration;
PID_State				yaw_pid_state;


//初始化为走正方向90
void yawPID_Init(void){

	u16 x;
	
	yaw_pid_state.actual=90-YAW;
	yaw_pid_state.target=90;
	yaw_pid_state.time_delta=1;
	yaw_pid_state.previous_error=0;
	yaw_pid_state.integral=0;
	yaw_pid_state.output=0;

#ifdef	INITIALIZE
	yaw_pid_calibration.kp=0;
	yaw_pid_calibration.ki=0;
	yaw_pid_calibration.kd=0;
	x=0;
	STM32_FLASH_Write(KP1_SAVE_ADDR,&x,1);
	STM32_FLASH_Write(KI1_SAVE_ADDR,&x,1);
	STM32_FLASH_Write(KD1_SAVE_ADDR,&x,1);
#else
	STM32_FLASH_Read(KP1_SAVE_ADDR,&x,1);
	yaw_pid_calibration.kp=Int_To_Float(x);
	STM32_FLASH_Read(KI1_SAVE_ADDR,&x,1);
	yaw_pid_calibration.ki=Int_To_Float(x);
	STM32_FLASH_Read(KD1_SAVE_ADDR,&x,1);
	yaw_pid_calibration.kd=0;
#endif
		
}

void YAWPIDscan_Init(void){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;		
	
	RCC_APB1PeriphClockCmd(YAWPID_TIM_PORT_RCC,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period=200;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=(72-1); //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(YAWPID_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(YAWPID_TIM,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(YAWPID_TIM,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
//	TIM_Cmd(YAWPID_TIM,ENABLE); //使能定时器
	
}


//void TIM2_IRQHandler(void){
	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	
//	if(TIM_GetITStatus(YAWPID_TIM,TIM_IT_Update))
//	{
////		yaw_pid_state.actual=90-YAW;
////		yaw_pid_state.target=90;
////		
////		pid_iterate(yaw_pid_calibration,yaw_pid_state);
//		
//		
//		
//		
//	}
//	
//	TIM_ClearITPendingBit(YAWPID_TIM,TIM_IT_Update);
	
//}

void PID_changeAngle(short angle){
	
	short x;
//	short y;
	
	yaw_pid_state.target=angle;
	yaw_pid_state.actual=90-YAW;
	
	pid_iterate(yaw_pid_calibration,&yaw_pid_state);
	
	x=(short)yaw_pid_state.output;
	//y=(short)x;
	
	//printf("Yaw: %.3f  output: %.3f\r\n",YAW,yaw_pid_state.output);
	angle += x;
	
	changeAngle(angle);
	
}

void Change_PID(u8 type,u16 date){
	
	switch(type){
		case '1':
			STM32_FLASH_Write(KP1_SAVE_ADDR,&date,1);
			yaw_pid_calibration.kp=Int_To_Float(date);
			break;
		case '2':
			STM32_FLASH_Write(KI1_SAVE_ADDR,&date,1);
			yaw_pid_calibration.ki=Int_To_Float(date);
			break;
		case '3':
			STM32_FLASH_Write(KD1_SAVE_ADDR,&date,1);
			yaw_pid_calibration.kd=Int_To_Float(date);
			break;
		
	}
	
}


