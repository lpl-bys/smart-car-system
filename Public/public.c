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
			if(flag) return 1;//ÕÒµ½×Ó´®
		}
	return 0;
}


