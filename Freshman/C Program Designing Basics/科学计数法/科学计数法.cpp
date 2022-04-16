#include <stdio.h>
#include <math.h>
#include <string.h>
int main(){
	char str[100],m[100]={'\0'},a[20]={'\0'};
	gets(str);
	
	int i,j=0,zhishu=0,dot,fir;
	for(i=0;str[i]!=' ';i++) m[i]=str[i];
	
	for(;i<strlen(str);i++){
		if(str[i]<=57&&str[i]>=48){
			a[j]=str[i];
			j++;
		}
	}
	
	for(i=0;i<strlen(a);i++) zhishu+=(a[i]-48)*pow(10,strlen(a)-i-1);
	
	if(zhishu=0){
		for(i=0;i<=dot+8;i++) printf("%c",m[i]);
		printf("\n");
		return 0;
	}
	
	if(zhishu>0){
		for(i=0;i<=zhishu+2;i++){
			if(m[i]=='.') continue;
			else printf("%c",m[i]);
		}
		printf(".");
		for(;)
	}
}
