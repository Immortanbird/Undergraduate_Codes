#include <stdio.h>
#include <math.h> 
int main(){
	int n;
	scanf("%d",&n);
	
	int row,i,j,temp;
	for(row=1;row<=2*n-1;row++){							//控制行数
		temp=n;
		for(i=1;i<=abs(n-row);i++)							//打印空格 
			printf("  ");
		for(j=1;j<n-abs(n-row);j++){						//打印数字 
			printf("%-2d",temp);
			temp--;
		}
		for(j=j;j<=2*(n-abs(n-row))-1;j++){
			printf("%-2d",temp);
			temp++;
		}
		printf("\n");	
	} 
}
