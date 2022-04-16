#include <stdio.h>
int main(){
	int i,j,h;
	scanf("%d",&h);
	
	for(i=1;i<2*h;i++)
		printf("*");
	printf("\n");
	
	for(i=2;i<=h;i++){
		for(j=1;j<i;j++){
			printf(" ");
			if(j==i-1) printf("*");
		}
		for(j=1;j<2*(h-i);j++)
			printf(" ");
		if(i<h) printf("*");
		printf("\n");
	}
}
