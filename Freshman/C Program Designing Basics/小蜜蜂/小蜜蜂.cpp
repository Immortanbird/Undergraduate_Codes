#include <stdio.h>
int main(){
	int a,b,i;
	scanf("%d%d",&a,&b);
	
	long long d[1001];
	d[1]=1;
	d[2]=2;
	
	for(i=3;i<=b-a;i++){
		d[i]=d[i-1]+d[i-2];
	}
	
	printf("%ld\n",d[b-a]);
}
