#include "motor.h"
#include "stm32_flash.h"

u16 tim3_hper,tim3_lper,tim3_psc;
u8 pwm3_status,car_speed;

void motorInit(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(MOTOR_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=(MOTOR_ENA_PIN|MOTOR_ENB_PIN|MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_IN3_PIN|MOTOR_IN4_PIN);  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(MOTOR_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	GPIO_ResetBits(MOTOR_PORT,(MOTOR_ENA_PIN|MOTOR_ENB_PIN|MOTOR_IN1_PIN|MOTOR_IN2_PIN|MOTOR_IN3_PIN|MOTOR_IN4_PIN));
	
	
	
	pwm3_status=0;
	tim3_psc=(7200-1);		//周期20ms
	
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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM2 AND TIM3时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=tim3_lper;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE); //使能定时器
	
}

void TIM3_IRQHandler(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update))
	{
		
		if(!pwm3_status){
			
			TIM_Cmd(TIM3,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim3_hper;   //自动装载值
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //分频系数
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
			
			TIM_Cmd(TIM3,ENABLE);
			
			GPIO_SetBits(MOTOR_PORT,MOTOR_ENA_PIN);
			GPIO_SetBits(MOTOR_PORT,MOTOR_ENB_PIN);
			
			pwm3_status=1;
		}
		else{
			
			TIM_Cmd(TIM3,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim3_lper;   //自动装载值
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim3_psc; //分频系数
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
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

void controlSpeed(u16 speed_hpwm){	//周期20ms，PWM高电平计数值	180 ~ 20
	
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

