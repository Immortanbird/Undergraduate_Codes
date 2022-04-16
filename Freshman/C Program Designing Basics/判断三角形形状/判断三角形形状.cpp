#include <stdio.h>
int judge(int a,int b,int c){
	if (a+b>c&&a+c>b&&b+c>a) return(1);
	else return(0);
}

int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	
	if (judge(a,b,c)==0) {
		printf("non-triangle.\n");
		return(0);
	}
	
	if(a==b&&b==c) {
		printf("equilateral triangle.\n");
		return(0);
	}		
	
	if(a==b||b==c||c==a) 
		printf("isoceles triangle.\n");
	else printf("triangle.\n");
}
