#include "pidyaw.h"


PID_Calibration yaw_pid_calibration;
PID_State				yaw_pid_state;

float KP1 = 0,
			KI1 = 0,
			KD1 = 0;

//��ʼ��Ϊ��������90
void yawPID_Init(void){

	yaw_pid_state.actual=90-YAW;
	yaw_pid_state.target=90;
	yaw_pid_state.time_delta=1;
	yaw_pid_state.previous_error=0;
	yaw_pid_state.integral=0;
	yaw_pid_state.output=0;

	yaw_pid_calibration.kp=KP1;
	yaw_pid_calibration.ki=KI1;
	yaw_pid_calibration.kd=KD1;
		
}

void YAWPIDscan_Init(void){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;		
	
	RCC_APB1PeriphClockCmd(YAWPID_TIM_PORT_RCC,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period=200;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=(72-1); //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(YAWPID_TIM,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(YAWPID_TIM,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(YAWPID_TIM,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//��ʱ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
//	TIM_Cmd(YAWPID_TIM,ENABLE); //ʹ�ܶ�ʱ��
	
}


void TIM2_IRQHandler(void){
	
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
	
}

void PID_changeAngle(u8 angle){
	
	short x;
//	short y;
	
	yaw_pid_state.target=angle;
	yaw_pid_state.actual=90-YAW;
	
	pid_iterate(yaw_pid_calibration,&yaw_pid_state);
	
	x=(short)yaw_pid_state.output;
	//y=(short)x;
	
	//printf("Yaw: %.3f  output: %.3f\r\n",YAW,yaw_pid_state.output);
	
	changeAngle(angle+x);
	
}


