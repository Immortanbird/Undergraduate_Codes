#include <stdio.h>
int main(){
	int year;
	scanf("%d",&year);
	
	int k,remainder,base;
	k=(year-1900)/4;
	remainder=(year-1900)%4;
	
	if (remainder==0){
		base=((366+365+365+365)*k+121)%7;
		switch(base){
			case 0:printf("8\n");break;
			case 1:printf("14\n");break;
			case 2:printf("13\n");break;
			case 3:printf("12\n");break;
			case 4:printf("11\n");break;
			case 5:printf("10\n");break;
			case 6:printf("9\n");break;
		}
	}
	if (remainder==1){
		base=((366+365+365+365)*k+366+120)%7;
		switch(base){
			case 0:printf("8\n");break;
			case 1:printf("14\n");break;
			case 2:printf("13\n");break;
			case 3:printf("12\n");break;
			case 4:printf("11\n");break;
			case 5:printf("10\n");break;
			case 6:printf("9\n");break;
		}
	}
	if (remainder==2){
		base=((366+365+365+365)*k+731+120)%7;
		switch(base){
			case 0:printf("8\n");break;
			case 1:printf("14\n");break;
			case 2:printf("13\n");break;
			case 3:printf("12\n");break;
			case 4:printf("11\n");break;
			case 5:printf("10\n");break;
			case 6:printf("9\n");break;
		}
	}
	if (remainder==3){
		base=((366+365+365+365)*k+1096+120)%7;
		switch(base){
			case 0:printf("8\n");break;
			case 1:printf("14\n");break;
			case 2:printf("13\n");break;
			case 3:printf("12\n");break;
			case 4:printf("11\n");break;
			case 5:printf("10\n");break;
			case 6:printf("9\n");break;
		}
	} 
}
