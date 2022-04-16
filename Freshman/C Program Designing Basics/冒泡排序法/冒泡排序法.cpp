#include <stdio.h>
#define N 5
int main(){
	int a[N],i,m,n,t;
	for (i=1;i<=N;i++)
		scanf("%d",&a[i]);

	for(m=1;m<=N;m++)
		for(n=1;n<=N-m;n++)
			if(a[n]>a[n+1]){
				t=a[n];
				a[n]=a[n+1];
				a[n+1]=t;
			}
			
	for(i=1;i<=N;i++)
		printf("%d",a[i]);
} 
