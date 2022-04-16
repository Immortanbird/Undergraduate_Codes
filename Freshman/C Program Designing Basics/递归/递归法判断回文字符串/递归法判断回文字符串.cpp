#include <stdio.h>
#include <string.h>
#include <math.h>
int judge(char k[50],int op){
	int len=strlen(k);
	int n=fabs(len-op-1);
	if(op==-1) return 1;
	if(k[op]!=k[n]) return 0;
	else return judge(k,op-1);
}
int main(){
	char input[50];
	gets(input);
	
	if(strlen(input)==1||strlen(input)==0){
		printf("Yes\n");
		return 0;
	}
	
	switch(judge(input,strlen(input)-1)){
		case 0:printf("No\n");break;
		case 1:printf("Yes\n");break;
	}
}
