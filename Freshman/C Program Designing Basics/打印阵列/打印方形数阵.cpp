#include <stdio.h>
int main(){
	int i,n,s;
	scanf("%d",&n);
	
	if(n==1){
		printf("  1\n");
		return 0;
	}
	
	s=0;
	for(i=1;i<=n*n;i++){
		if(s==n-1){
			if(i<10){
				printf("  %d\n",i);
				s=0;
			}
			else{
				printf(" %d\n",i);
				s=0;
			}
		}
		else{
			if(i<10){
				printf("  %d",i);
				s=s+1;
			}
			else{
				printf(" %d",i);
				s=s+1;
			}
		}
	}
}
