#include "motor.h"
#include "stm32_flash.h"

u16 tim3_hper,tim3_lper,tim3_psc;
u8 pwm3_status,car_speed;

void motorInit(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=(MOTOR_ENA_PIN|MOTOR_ENB_PIN|MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_IN3_PIN|MOTOR_IN4_PIN);  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(MOTOR_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_ResetBits(MOTOR_PORT,(MOTOR_ENA_PIN|MOTOR_ENB_PIN|MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_IN3_PIN|MOTOR_IN4_PIN));
	
	
	
	pwm3_status=0;
	tim3_psc=(7200-1);		//����20ms
	
#ifdef INITIALIZE
	tim3_hper=45;
	tim3_lper=155;
	STM32_FLASH_Write(SPEED_HPER_SAVE_ADDR,&tim3_hper,1);
	STM32_FLASH_Write(SPEED_LPER_SAVE_ADDR,&tim3_lper,1);
#else
	STM32_FLASH_Read(SPEED_HPER_SAVE_ADDR,&tim3_hper,1);
	STM32_FLASH_Read(SPEED_LPER_SAVE_ADDR,&tim3_lper,1);
#endif


	car_speed=0;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ��TIM2 AND TIM3ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period=tim3_lper;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //������ʱ���ж�
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//��ʱ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��
	
}

void TIM3_IRQHandler(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update))
	{
		
		if(!pwm3_status){
			
			TIM_Cmd(TIM3,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim3_hper;   //�Զ�װ��ֵ
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //��Ƶϵ��
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
			
			TIM_Cmd(TIM3,ENABLE);
			
			GPIO_SetBits(MOTOR_PORT,MOTOR_ENA_PIN);
			GPIO_SetBits(MOTOR_PORT,MOTOR_ENB_PIN);
			
			pwm3_status=1;
		}
		else{
			
			TIM_Cmd(TIM3,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim3_lper;   //�Զ�װ��ֵ
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //��Ƶϵ��
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
			
			TIM_Cmd(TIM3,ENABLE);
			
			GPIO_ResetBits(MOTOR_PORT,MOTOR_ENA_PIN);
			GPIO_ResetBits(MOTOR_PORT,MOTOR_ENB_PIN);
			
			pwm3_status=0;
		}
		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	
}

void controlMotor(u8 direction){
	
	if(direction){		
		
		switch(direction){
			case GO_FORWARD :
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN1_PIN);
				GPIO_SetBits(MOTOR_PORT,MOTOR_IN2_PIN);
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN3_PIN);
				GPIO_SetBits(MOTOR_PORT,MOTOR_IN4_PIN);
				break;
			
			case GO_BACKWARD :
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN2_PIN);
				GPIO_SetBits(MOTOR_PORT,MOTOR_IN1_PIN);
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN4_PIN);
				GPIO_SetBits(MOTOR_PORT,MOTOR_IN3_PIN);
				break;
			
			default :
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN2_PIN);
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN1_PIN);
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN4_PIN);
				GPIO_ResetBits(MOTOR_PORT,MOTOR_IN3_PIN);
				break;
		}
		
	}
		
	
}

void controlSpeed(u16 speed_hpwm){	//����20ms��PWM�ߵ�ƽ����ֵ	180 ~ 20
	
//	switch(car_speed){
//		case 3 :
//			tim3_hper+=2;
//			tim3_lper-=2;
////			printf("SPEED-hper: %d\r\n",tim3_hper);
//			car_speed=0;
//			break;
//		case 5 :
//			tim3_hper-=2;
//			tim3_lper+=2;
////			printf("SPEED-hper: %d\r\n",tim3_hper);
//			car_speed=0;
//			break;
//		default :
//			break;
//		
//	}
	
	if(speed_hpwm>180) speed_hpwm=180;
	else if(speed_hpwm<20) speed_hpwm=20;
	
	tim3_hper = speed_hpwm;
	tim3_lper = 200-speed_hpwm;
	
	STM32_FLASH_Write(SPEED_HPER_SAVE_ADDR,&tim3_hper,1);
	STM32_FLASH_Write(SPEED_LPER_SAVE_ADDR,&tim3_lper,1);
//	printf("SPEED-hper: %d\r\n",tim3_hper);
	
}

