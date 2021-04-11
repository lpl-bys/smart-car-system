#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "servo.h"
#include "motor.h"
#include "JY901.h"
#include "pid.h"
#include "pidyaw.h"
#include "dma.h"
#include "ESP8266.h"

extern u8 TCP_CONTINUE,CUT_CONNECT_STATION,CONNECT_AP,WIFI_MODE;

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main(void){
	
	u8 j;
	u16 i;
	u8 flag,conflag;
	
	flag=1;
	conflag=1;
//	short j;
	
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ����� ��2��
	servoInit();
	motorInit();
	yawPID_Init();
	LED_Init();
//	USART1_Init(115200);
//	DMA1_USARTX_Init();
	USART2_Init(9600);
//	USART3_Init(115200);
//	ESP8266_Init();
	
	delay_ms(1000);
	UART2_Put_String(UNLOCK);
	delay_ms(10);
	UART2_Put_String(SETALG6);
	delay_ms(100);
	UART2_Put_String(OPENAUTOGYRO);
	delay_ms(100);
	UART2_Put_String(ZTOZERO);
	delay_ms(100);
//	
//	printf("TEST\r\n");
	DMA1_USARTX_Init();
	USART3_Init(115200);
	ESP8266_Init();
	Start_Station();
	
	
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
//			printf("���ڽ��м��ٶ�У׼\r\n");
			UART2_Put_String(ACCCALSW);delay_ms(100);//�ȴ�ģ���ڲ��Զ�У׼�ã�ģ���ڲ����Զ�������Ҫһ����ʱ��
			UART2_Put_String(SAVACALSW);delay_ms(100);//���浱ǰ����
//			printf("���ٶ�У׼���\r\n");
		}
		//printf("Angle:%.3f %.3f %.3f\r\n",(float)stcAngle.Angle[0]/32768*180,(float)stcAngle.Angle[1]/32768*180,(float)stcAngle.Angle[2]/32768*180);
		YAW=(float)stcAngle.Angle[2]/32768*180;
	//	j=(short)YAW;
		PID_changeAngle(YawTarget);
//		printf("Yaw: %.3f  %d\r\n ",YAW,j);
//		if(i%5==0)
//			printf("Yaw: %.3f\r\n",YAW);
		if(i%5==0){
			if((!CUT_CONNECT_STATION)||CONNECT_AP){
//				if(TCP_CONTINUE)	AT_CIPSEND("Hello!","6",WIFI_MODE);			
//				else 							AT_CIPSTART("TCP","192.168.137.1","23333");
				if(!TCP_CONTINUE)	AT_CIPSTART("TCP","192.168.137.1","23333");
				else if(conflag){
					AT_CIPSEND("TCP-Builded!","12",WIFI_MODE);	
					conflag=0;
				}
			}
			else if(flag){
				Turn_AP();
				flag=0;
			}
		}
//		delay_ms(10);
		
	}
}

