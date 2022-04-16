#include <stdio.h>
#include <math.h>
int main(){
	char str1[2],str2[6],str3[6];
	gets(str1);
	gets(str2);
	gets(str3);
	
	int input[11],i;
	input[0]=str1[0]-48;
	for(i=1;i<6;i++){
		input[i]=str2[i-1]-48;
	}
	for(i=6;i<11;i++){
		input[i]=str3[i-6]-48;
	}
	
	i=3*(input[0]+input[2]+input[4]+input[6]+input[8]+input[10])+input[1]+input[3]+input[5]+input[7]+input[9]-1;
	i=9-i%10;
	printf("%d\n",i);
} 
