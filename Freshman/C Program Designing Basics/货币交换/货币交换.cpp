#include <stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	if(n%8!=0) printf("No change.\n");
	else printf("%d,%d,%d\n",25*n/4,15*n/2,45*n/8);
} 
