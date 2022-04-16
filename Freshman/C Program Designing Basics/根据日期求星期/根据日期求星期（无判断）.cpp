#include <stdio.h>
int main(){
	int year,month,day;
	scanf("%d%d%d",&year,&month,&day);
	
	int k,remainder;
	k=(year-1900)/4;
	remainder=(year-1900)%4;
	
	if (remainder==0){
		switch (month-1){
			case 0:printf("%d\n",((366+365+365+365)*k+day-1)%7);break;
			case 1:printf("%d\n",((366+365+365+365)*k+31+day-1)%7);break;
			case 2:printf("%d\n",((366+365+365+365)*k+60+day-1)%7);break;
			case 3:printf("%d\n",((366+365+365+365)*k+91+day-1)%7);break;
			case 4:printf("%d\n",((366+365+365+365)*k+121+day-1)%7);break;
			case 5:printf("%d\n",((366+365+365+365)*k+152+day-1)%7);break;
			case 6:printf("%d\n",((366+365+365+365)*k+182+day-1)%7);break;
			case 7:printf("%d\n",((366+365+365+365)*k+213+day-1)%7);break;
			case 8:printf("%d\n",((366+365+365+365)*k+244+day-1)%7);break;
			case 9:printf("%d\n",((366+365+365+365)*k+274+day-1)%7);break;
			case 10:printf("%d\n",((366+365+365+365)*k+305+day-1)%7);break;
			case 11:printf("%d\n",((366+365+365+365)*k+335+day-1)%7);break;
		}
		return 0;
	}
	if (remainder==1){
		switch (month-1){
			case 0:printf("%d\n",((366+365+365+365)*k+366+day-1)%7);break;
			case 1:printf("%d\n",((366+365+365+365)*k+366+31+day-1)%7);break;
			case 2:printf("%d\n",((366+365+365+365)*k+366+59+day-1)%7);break;
			case 3:printf("%d\n",((366+365+365+365)*k+366+90+day-1)%7);break;
			case 4:printf("%d\n",((366+365+365+365)*k+366+120+day-1)%7);break;
			case 5:printf("%d\n",((366+365+365+365)*k+366+151+day-1)%7);break;
			case 6:printf("%d\n",((366+365+365+365)*k+366+181+day-1)%7);break;
			case 7:printf("%d\n",((366+365+365+365)*k+366+212+day-1)%7);break;
			case 8:printf("%d\n",((366+365+365+365)*k+366+243+day-1)%7);break;
			case 9:printf("%d\n",((366+365+365+365)*k+366+273+day-1)%7);break;
			case 10:printf("%d\n",((366+365+365+365)*k+366+304+day-1)%7);break;
			case 11:printf("%d\n",((366+365+365+365)*k+366+334+day-1)%7);break;
		}
		return 0;
	}
	if (remainder==2){
		switch (month-1){
			case 0:printf("%d\n",((366+365+365+365)*k+731+day-1)%7);break;
			case 1:printf("%d\n",((366+365+365+365)*k+731+31+day-1)%7);break;
			case 2:printf("%d\n",((366+365+365+365)*k+731+59+day-1)%7);break;
			case 3:printf("%d\n",((366+365+365+365)*k+731+90+day-1)%7);break;
			case 4:printf("%d\n",((366+365+365+365)*k+731+120+day-1)%7);break;
			case 5:printf("%d\n",((366+365+365+365)*k+731+151+day-1)%7);break;
			case 6:printf("%d\n",((366+365+365+365)*k+731+181+day-1)%7);break;
			case 7:printf("%d\n",((366+365+365+365)*k+731+212+day-1)%7);break;
			case 8:printf("%d\n",((366+365+365+365)*k+731+243+day-1)%7);break;
			case 9:printf("%d\n",((366+365+365+365)*k+731+273+day-1)%7);break;
			case 10:printf("%d\n",((366+365+365+365)*k+731+304+day-1)%7);break;
			case 11:printf("%d\n",((366+365+365+365)*k+731+334+day-1)%7);break;
		}
		return 0;
	}
	
	if (remainder==3){
		switch (month-1){
			case 0:printf("%d\n",((366+365+365+365)*k+1096+day-1)%7);break;
			case 1:printf("%d\n",((366+365+365+365)*k+1096+31+day-1)%7);break;
			case 2:printf("%d\n",((366+365+365+365)*k+1096+59+day-1)%7);break;
			case 3:printf("%d\n",((366+365+365+365)*k+1096+90+day-1)%7);break;
			case 4:printf("%d\n",((366+365+365+365)*k+1096+120+day-1)%7);break;
			case 5:printf("%d\n",((366+365+365+365)*k+1096+151+day-1)%7);break;
			case 6:printf("%d\n",((366+365+365+365)*k+1096+181+day-1)%7);break;
			case 7:printf("%d\n",((366+365+365+365)*k+1096+212+day-1)%7);break;
			case 8:printf("%d\n",((366+365+365+365)*k+1096+243+day-1)%7);break;
			case 9:printf("%d\n",((366+365+365+365)*k+1096+273+day-1)%7);break;
			case 10:printf("%d\n",((366+365+365+365)*k+1096+304+day-1)%7);break;
			case 11:printf("%d\n",((366+365+365+365)*k+1096+334+day-1)%7);break;
		}
		return 0;
	}
}
