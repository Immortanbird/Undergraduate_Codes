#include <stdio.h>
#include <math.h>
int main(){
	int n;
	scanf("%d",&n);
	
	int i,j,s,temp,x,t=0;
	for(i=pow(10,n-1);i<pow(10,n);i++){
		temp=i;
		s=0;
		for(j=n-1;j>=0;j--){ 
			x=temp/pow(10,j);
			temp=temp-x*pow(10,j);
			s=s+pow(x,n);
		}
		if(s==i){
			printf("%d\n",i);
			t++;
		}
	}
	if(t==0) printf("No output.\n");
} 
