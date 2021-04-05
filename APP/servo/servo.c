#include "servo.h"
#include "led.h"

u16 tim4_hper,tim4_lper,tim4_psc;
u8 pwm1_status;

void servoInit(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(SERVO_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=SERVO_PIN;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(SERVO_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
	
	GPIO_ResetBits(SERVO_PORT,SERVO_PIN);   
	
	
	pwm1_status=0;
	tim4_psc=(36-1);
	tim4_hper=3000;
	tim4_lper=37000;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period=tim4_lper;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=tim4_psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //开启定时器中断
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//定时器中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(TIM4,ENABLE); //使能定时器
		
}

void TIM4_IRQHandler(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update))
	{
		
		if(!pwm1_status){
			
			TIM_Cmd(TIM4,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim4_hper;   //自动装载值
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim4_psc; //分频系数
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
			TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
			
			TIM_Cmd(TIM4,ENABLE);
			
			GPIO_SetBits(SERVO_PORT,SERVO_PIN);
			
			pwm1_status=1;
		}
		else{
			
			TIM_Cmd(TIM4,DISABLE);
			
			TIM_TimeBaseInitStructure.TIM_Period=tim4_lper;   //自动装载值
			TIM_TimeBaseInitStructure.TIM_Prescaler=tim4_psc; //分频系数
			TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
			TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
			TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
			
			TIM_Cmd(TIM4,ENABLE);
			
			GPIO_ResetBits(SERVO_PORT,SERVO_PIN);
			
			pwm1_status=0;
		}
		
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	
}

void toCenter(void){
	
	tim4_psc=(36-1);
	tim4_hper=3000;
	tim4_lper=37000;

}

void changeAngle(u8 angle){
	
	float temp;
	
	if(angle>105) angle=105;
	else if(angle<75)	angle=75;
	
	tim4_psc=(36-1);
	
	temp=((float)(angle)/9.0);	//(angle/180*2000+500)*2
	tim4_hper=temp*200+1000;	
	
	tim4_lper=40000-tim4_hper;
	
}



