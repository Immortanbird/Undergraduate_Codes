#include <stdio.h>
#include <math.h> 
int main(){
	int a[100];
	int n,i,j,k;
	for(n=1;n<=10;n++){
		scanf("%d",&a[n]);
		if(a[n]==0){
			scanf("%d",&a[n+1]);
			break;
		}
	}
	
	int temp,counter;
	int x[100];
	for(k=1;k<=n-2;k=k+2){
		counter=0;
		for(i=a[k];i<=a[k+1];i++){
			if(i%2==1||i<1024||i>9998) continue;
			temp=i;
			for(j=4;j>=1;j--){
			x[j]=temp/pow(10,j-1);
			temp=temp-x[j]*pow(10,j-1);
			}
			if(x[1]!=x[2]&&x[1]!=x[3]&&x[1]!=x[4]&&x[2]!=x[3]&&x[2]!=x[4]&&x[3]!=x[4]){
				printf("%d  ",i);
				counter++;
			}
		}
		if(counter==0) printf("Error\n");
		else{
			printf("\n");
			printf("counter=%d\n",counter); 
		}
	}
} 
