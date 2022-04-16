#include <stdio.h>
#include <math.h>
int main(){
	int n;
	scanf("%d",&n);
	
	if(n==0){
		printf("0\n");
		return 0;
	}
	
	int i,j,temp,s=0,step;
	step=n*n;
	for(i=step;i<pow(10,n-1);i+=step);
	for(;i<pow(10,n);i+=step){
		for(j=1;j<n;j++){
			temp=(int)(i/pow(10,j))%((n-j)*(n-j));
			if(temp!=0) break;
		} 
		if(temp==0) s++;
	}
	printf("%d\n",s);
}
