#include <stdio.h>
#include <math.h>
int main(){
	int n;
	scanf("%d",&n);
	
	int temp=n,s=-1;
	do{											//ȷ��λ�� 
		temp=temp/10;
		s++;
	}while(temp>0);
	
	int a[10],i,j;
	temp=n;
	for(i=s;i>=0;i--){							//ȡ�� 
		a[i]=temp/pow(10,i);
		temp=temp-a[i]*pow(10,i);
	}
	
	for(i=0;i<=s;i++){							//ð������ 
		for(j=0;j<=s-1;j++){
			if(a[j]<a[j+1]){
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	
	for(i=0;i<=s;i++)
		printf("%d",a[i]);
	printf("\n");
}
