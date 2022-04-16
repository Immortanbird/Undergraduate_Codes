#include <stdio.h>
int main(){
	int row,n;
	scanf("%d%d",&row,&n);
	
	if(row==1){
		printf("%d\n",n);
		return 0;
	}
	
	int i,j,temp;
	if(row%2==1){													//奇数行 
		temp=n;
		for(i=1;i<=(3*row-3)/2;i++){								//第一行前半部分 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=(3*row-1)/2;i<=3*row-2;i++){							//第一行后半部分 
			printf("%d",temp%10);
			temp--;
			if(i!=3*row-2) printf(" ");
			else printf("\n");
		}
		
		for(i=2;i<=row-1;i++){										//打印中间行 
			for(j=1;j<=2*(i-1);j++) 								//打印行首空格 
				printf(" ");
			printf("%d",(n+i-1)%10);								//打印行首
			for(j=1;j<=6*row-4*i-3;j++)								//打印中间空格 
				printf(" ");
			printf("%d\n",(n+i-1)%10);								//打印行末 
		}
		
		for(i=1;i<=2*(row-1);i++){									//最后一行行首空格 
			printf(" ");
		}
		temp=n+row-1;
		for(i=1;i<=(row-1)/2;i++){									//最后一行前半部分 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=(row+1)/2;i<=row;i++){								//最后一行后半部分 
			printf("%d",temp%10);
			temp--;
			if(i!=row) printf(" ");
			else printf("\n");
		}
	}
	else{															//偶数行 
		temp=n;
		for(i=1;i<=(3*row-2)/2;i++){								//第一行前半部分 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=1;i<=(3*row-2)/2;i++){								//第一行后半部分
			temp--;
			printf("%d",temp%10);
			if(i!=(3*row-2)/2) printf(" ");
			else printf("\n");
		}
		
		for(i=2;i<=row-1;i++){										//打印中间行 
			for(j=1;j<=2*(i-1);j++) 								//打印行首空格 
				printf(" ");
			printf("%d",(n+i-1)%10);								//打印行首
			for(j=1;j<=6*row-4*i-3;j++)								//打印中间空格 
				printf(" ");
			printf("%d\n",(n+i-1)%10);								//打印行末 
		}
		
		for(i=1;i<=2*(row-1);i++){									//最后一行行首空格 
			printf(" ");
		}
		temp=n+row-1;
		for(i=1;i<=row/2;i++){										//最后一行前半部分 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=1;i<=row/2;i++){										//最后一行后半部分
			temp--;
			printf("%d",temp%10);
			if(i!=row/2) printf(" ");
			else printf("\n");
		}
	}
} 
