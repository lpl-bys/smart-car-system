#include "ESP8266.h"

extern char send_buffer[DMA1_USARTX_BUFF_SIZE];
extern char receive_buffer[DMA1_USARTX_BUFF_SIZE];
u8 TAG_OK,TCP_CONTINUE,CUT_CONNECT_STATION,CONNECT_AP,WIFI_MODE;

void ESP8266_Init(void){
	TAG_OK=0;
	TCP_CONTINUE=0;
	CUT_CONNECT_STATION=0;
	CONNECT_AP=0;
	WIFI_MODE=0;
}

u8 AT_CWMODE(char MODE){
	u32 telen;
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT+CWMODE=");
	strcat(send_buffer,&MODE);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);;
	Send_Data(telen);
	delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT(void){
	u8 i;
	
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT\r\n");
	Send_Data(4);
	delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
//	led7=!led7;
//	delay_ms(500);
	return 1;
}

u8 AT_RST(void){
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT+RST\r\n");
	Send_Data(8);
	delay_ms(3000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT_CWJAP(char* ssid,char* pwd){
	u32 telen,i;
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT+CWJAP=\"");
	strcat(send_buffer,ssid);
	strcat(send_buffer,"\",\"");
	strcat(send_buffer,pwd);
	strcat(send_buffer,"\"");
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);
	Send_Data(telen);
	for(i=0;i<66;i++)
		delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT_CIPSTART(char* type,char* ip,char* port){
	u32 telen,i;
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT+CIPSTART=\"");
	strcat(send_buffer,type);
	strcat(send_buffer,"\",\"");
	strcat(send_buffer,ip);
	strcat(send_buffer,"\",");
	strcat(send_buffer,port);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);
	Send_Data(telen);
	delay_ms(6000);
	for(i=0;i<66;i++)
		delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		TCP_CONTINUE=1;
		return 0;
	}
	return 1;
}

u8 AT_CIPSEND(char* date,char* datelen,u8 MODE){
	u32 telen;
	memset(send_buffer,0,sizeof(send_buffer));
//	memset(receive_buffer,0,sizeof(receive_buffer));
	strcpy(send_buffer,"AT+CIPSEND=");
	if(MODE==2){
		strcat(send_buffer,"0,");
	}
	strcat(send_buffer,datelen);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);;
	Send_Data(telen);
	delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		memset(send_buffer,0,sizeof(send_buffer));
		strcpy(send_buffer,date);
		strcat(send_buffer,"\r\n");
		telen=strlen(send_buffer);
		Send_Data(telen);
		delay_ms(2000);
		return 0;
	//	DMA_Cmd(DMA1_USARTX_RX_CHANNELX,ENABLE);
	}
//	DMA_Cmd(DMA1_USARTX_RX_CHANNELX,ENABLE);
	return 1;
}

u8 AT_CIPCLOSE(void){
	memset(send_buffer,0,sizeof(send_buffer));
	strcpy(send_buffer,"AT+CIPCLOSE\r\n");
	Send_Data(13);
	delay_ms(3000);
	if(TAG_OK){
		TAG_OK=0;
		TCP_CONTINUE=0;
		return 0;
	}
	return 1;
}

u8 AT_CWQAP(void){
	memset(send_buffer,0,sizeof(send_buffer));
	strcpy(send_buffer,"AT+CWQAP\r\n");
	Send_Data(10);
	delay_ms(3000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT_CIPMUX(char MODE){
	u32 telen;
	memset(send_buffer,0,sizeof(send_buffer));
	strcpy(send_buffer,"AT+CIPMUX=");
	strcat(send_buffer,&MODE);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);;
	Send_Data(telen);
	delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT_CIPSERVER(char MODE,char* port){
	u32 telen;
	memset(send_buffer,0,sizeof(send_buffer));
	strcpy(send_buffer,"AT+CIPSERVER=");
	strcat(send_buffer,&MODE);
	strcat(send_buffer,",");
	strcat(send_buffer,port);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);;
	Send_Data(telen);
	delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}

u8 AT_CWSAP(char* ssid,char* pwd,char* chl,char* ecn){
	u32 telen,i;
	memset(send_buffer,0,sizeof(send_buffer));
	strcpy(send_buffer,"AT+CWSAP=\"");
	strcat(send_buffer,ssid);
	strcat(send_buffer,"\",\"");
	strcat(send_buffer,pwd);
	strcat(send_buffer,"\",");
	strcat(send_buffer,chl);
	strcat(send_buffer,",");
	strcat(send_buffer,ecn);
	strcat(send_buffer,"\r\n");
	telen=strlen(send_buffer);
	Send_Data(telen);
	for(i=0;i<33;i++)
		delay_ms(2000);
	if(TAG_OK){
		TAG_OK=0;
		return 0;
	}
	return 1;
}


void Start_Station(void){
	while(AT());
//	led1=0;
//	printf("AT	---		OK\r\n");
//	memset(send_buffer,0,sizeof(send_buffer));
//	strcpy(send_buffer,"ATOK\r\n");
//	Send_Data(6);
	
	while(AT_CWMODE('1'));
	WIFI_MODE=1;
	
//	memset(send_buffer,0,sizeof(send_buffer));
//	strcpy(send_buffer,"WIFIMODE\r\n");
//	Send_Data(10);
//	led2=0;
	AT_RST();
//	printf("RST	---		OK\r\n");
//	led3=0;
	while(AT());
//	printf("AT	---		OK\r\n");
//	led4=0;
//	AT_CWJAP("Honor 10","925a4077bc72");
	
//	led5=0;
//	AT_CIPSTART("TCP","192.168.43.174","10500");
//	led6=0;
}

void Turn_AP(void){
	AT_CIPCLOSE();
	TCP_CONTINUE=0;
	AT_CWQAP();
	CUT_CONNECT_STATION=1;
	
	AT_CWMODE('2');
	WIFI_MODE=2;
	AT_RST();
	while(AT());
	AT_CWSAP("ESP8266","1234","11","0");
	AT_CIPMUX('1');
	AT_CIPSERVER('1',"10500");
	CONNECT_AP=1;
	TCP_CONTINUE=1;
}

