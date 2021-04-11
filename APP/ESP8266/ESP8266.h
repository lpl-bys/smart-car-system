#ifndef _ESP8266_H
#define _ESP8266_H

#include "system.h"
#include <string.h>
#include "dma.h"
#include "SysTick.h"
#include "LED.h"
#include "usart.h"

u8 AT_CWMODE(char MODE);
u8 AT(void);
u8 AT_RST(void);
u8 AT_CWJAP(char* ssid,char* pwd);
u8 AT_CIPSTART(char* type,char* ip,char* port);
u8 AT_CIPSEND(char* date,char* datelen,u8 MODE);
u8 AT_CWQAP(void);
u8 AT_CIPCLOSE(void);
u8 AT_CIPMUX(char MODE);
u8 AT_CIPSERVER(char MODE,char* port);
u8 AT_CWSAP(char* ssid,char* pwd,char* chl,char* ecn);

void Start_Station(void);
void ESP8266_Init(void);
void Turn_AP(void);






#endif
