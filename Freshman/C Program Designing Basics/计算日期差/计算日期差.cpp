#include <stdio.h>
int main(){
	int a,b,c,d,r;
	scanf("%d:%d%d:%d",&a,&b,&c,&d);
	
	r=30*(c-a)+b-d;
	if (r<0)
		printf("Duang\n");
	else
		printf("%d\n",r);
} 
