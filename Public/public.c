#include "public.h"

u8 String_Compare(char* str1,char* str2,u32 str1n,u32 str2n){
	u32 i,j,te;
	u8 flag;
	flag=1;
	te=str1n-str2n+1;
	for(i=0;i<te;i++)
		if(str1[i]==str2[0]){
			for(j=0;j<str2n;j++)
				if(str1[j+i]!=str2[j]){
					flag=0;
					break;
				}
			if(flag) return 1;//找到子串
		}
	return 0;
}

u32 String_To_Num(char* str){//例：输入“233333E”（字符串）,输出233333（数值）
	
	u8 strn,i;
	u32 x,num;
	
	strn=strlen(str);	// "xxxxE"
	x=1;num=0;
	
	if(str[strn-1]=='E')
		for(i=strn-1;i>0;i--){
			num+=(str[i-1]-'0')*x;
			x*=10;
		}
	
	return num;
}

u32 Float_To_Int(float f,u8 dotn){
	
	u8 i;
	u32 rec,x;
	
	x=10;
	
	for(i=0;i<dotn;i++)	x*=10;
	
	rec=f*x;
	rec-=(rec%10);
	rec+=dotn;
	
	return rec;
}

float Int_To_Float(u32 Int){
	
	u8 dotn,i;
	float rec,x;
	
	x=0.1;
	
	dotn=Int%10;
	Int-=dotn;
	
	for(i=0;i<dotn;i++)	x*=0.1;
	
	rec=Int*x;
	
	return rec;
	
	
	
}



