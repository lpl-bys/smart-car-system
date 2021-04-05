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

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//进入加速度校准模式
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//保存当前配置
//char ONLYANGLE[6] = {0XFF,0XAA,0X02,0X08,0X00,0X00};//仅回传角度包
char SETALG6[6] = {0XFF,0XAA,0X24,0X01,0X00,0X00};//设置成6轴算法
char OPENAUTOGYRO[6] = {0XFF,0XAA,0X63,0X00,0X00,0X00};//选择陀螺仪自动校准
char ZTOZERO[6] = {0XFF,0XAA,0X01,0X04,0X00,0X00};//Z轴角度归零
char UNLOCK[6] = {0XFF,0XAA,0X69,0X88,0XB5,0X00};//解锁

float YAW;

