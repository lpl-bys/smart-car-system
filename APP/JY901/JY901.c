#include "JY901.h"

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//������ٶ�У׼ģʽ
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//���浱ǰ����
//char ONLYANGLE[6] = {0XFF,0XAA,0X02,0X08,0X00,0X00};//���ش��ǶȰ�
char SETALG6[6] = {0XFF,0XAA,0X24,0X01,0X00,0X00};//���ó�6���㷨
char OPENAUTOGYRO[6] = {0XFF,0XAA,0X63,0X00,0X00,0X00};//ѡ���������Զ�У׼
char ZTOZERO[6] = {0XFF,0XAA,0X01,0X04,0X00,0X00};//Z��Ƕȹ���
char UNLOCK[6] = {0XFF,0XAA,0X69,0X88,0XB5,0X00};//����

float YAW;

