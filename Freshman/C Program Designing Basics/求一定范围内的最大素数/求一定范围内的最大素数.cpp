#include <stdio.h>
#include <math.h>
int main(){
	int num;
	scanf("%d",&num);
	int factor,i;
	i=1;
	
	while(num>1&&i==1){
		i=0;
		for(factor=2;factor<=sqrt(num);factor++){
			if (num%factor==0)
				i=1;
		}
		num--;
	}
	printf("The max prime number is %d.\n",num+1);
} 
