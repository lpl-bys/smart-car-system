#include "action.h"


void actionInit(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(QDCOM_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin= (ENA_PIN|ENB_PIN|IN1_PIN|IN2_PIN|IN3_PIN|IN4_PIN);  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(QDCOM_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	
	GPIO_ResetBits(QDCOM_PORT,(ENA_PIN|ENB_PIN|IN1_PIN|IN2_PIN|IN3_PIN|IN4_PIN));
	
}


void goStraight(u8 speed){
	
	GPIO_ResetBits(QDCOM_PORT,(IN1_PIN|IN4_PIN));
	GPIO_SetBits(QDCOM_PORT,(IN2_PIN|IN3_PIN));
	
	while(1){
		
		GPIO_SetBits(QDCOM_PORT,(ENA_PIN|ENB_PIN));
		delay_ms(speed);
		GPIO_ResetBits(QDCOM_PORT,(ENA_PIN|ENB_PIN));
		delay_ms(100-speed);
		
	}
	
}


