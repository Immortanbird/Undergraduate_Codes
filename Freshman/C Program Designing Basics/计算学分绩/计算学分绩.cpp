#include <stdio.h>
int main(){
	float a;
	int b; 
	scanf("%f%d",&a,&b);
	if (a>100||a<0){
		printf("Error.\n");
		return(0);
	}
	if (a<=100&&a>=90){
		printf("%.2f\n",1.0*b*1.4);
		return(0);
	}
	if (a<90&&a>=80){
		printf("%.2f\n",1.0*b*1.2);
		return(0);
	}
	if (a<80&&a>=70){
		printf("%.2f\n",1.0*b*1.1);
		return(0);
	}
	if (a<70&&a>=60){
		printf("%.2f\n",1.0*b);
		return(0);
	}
	if (a<60&&a>=0){
		printf("0\n");
		return(0);
	}	
} 
