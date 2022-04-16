#include <stdio.h>
int sum(int m,int n,int d){
	if(n==m) return m;
	else return n+sum(m,n-d,d);
}
int main(){
	int m,n,d;
	scanf("%d%d%d",&m,&n,&d);
	printf("The sum is %d.\n",sum(m,n,d));
}
