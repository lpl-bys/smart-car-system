#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "servo.h"
#include "motor.h"
#include "JY901.h"
#include "pid.h"
#include "pidyaw.h"


/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main(void){
	
	u8 j;
	u16 i;
//	short j;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组 分2组
	servoInit();
	motorInit();
	yawPID_Init();
	LED_Init();
	USART1_Init(115200);
	USART2_Init(9600);
	
	delay_ms(1000);
	UART2_Put_String(UNLOCK);
	delay_ms(10);
	UART2_Put_String(SETALG6);
	delay_ms(100);
	UART2_Put_String(OPENAUTOGYRO);
	delay_ms(100);
	UART2_Put_String(ZTOZERO);
	delay_ms(100);
	
	
	while(1){
//		GPIO_ResetBits(LED_PORT,LED_PIN);
//		delay_ms(500);
//		GPIO_SetBits(LED_PORT,LED_PIN);
//		delay_ms(500);
		
		delay_ms(200);
		i++;
		if(i>500)
		{
			i = 0;
//			printf("正在进行加速度校准\r\n");
			UART2_Put_String(ACCCALSW);delay_ms(100);//等待模块内部自动校准好，模块内部会自动计算需要一定的时间
			UART2_Put_String(SAVACALSW);delay_ms(100);//保存当前配置
//			printf("加速度校准完成\r\n");
		}
		//printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
		YAW=(float)stcAngle.Angle[2]/32768*180;
	//	j=(short)YAW;
		PID_changeAngle(YawTarget);
//		printf("Yaw: %.3f  %d\r\n ",YAW,j);
//		if(i%5==0)
//			printf("Yaw: %.3f\r\n",YAW);
//		delay_ms(10);
		
	}
}

