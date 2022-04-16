#include <stdio.h>
#include <math.h>
double sum(int n){
	if(n==1) return 1;
	else pow(-1,(double)n)*(1/(double)n)+sum(n-1);
}

int main(){
	int n;
	scanf("%d",&n);
	if(sum(n)==1.000000) printf("1\n");
	else printf("%lf\n",sum(n));
}
