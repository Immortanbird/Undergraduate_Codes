#include <stdio.h>
int main(){
	int row,n;
	scanf("%d%d",&row,&n);
	
	if(row==1){
		printf("%d\n",n);
		return 0;
	}
	
	int i,j,temp;
	if(row%2==1){													//������ 
		temp=n;
		for(i=1;i<=(3*row-3)/2;i++){								//��һ��ǰ�벿�� 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=(3*row-1)/2;i<=3*row-2;i++){							//��һ�к�벿�� 
			printf("%d",temp%10);
			temp--;
			if(i!=3*row-2) printf(" ");
			else printf("\n");
		}
		
		for(i=2;i<=row-1;i++){										//��ӡ�м��� 
			for(j=1;j<=2*(i-1);j++) 								//��ӡ���׿ո� 
				printf(" ");
			printf("%d",(n+i-1)%10);								//��ӡ����
			for(j=1;j<=6*row-4*i-3;j++)								//��ӡ�м�ո� 
				printf(" ");
			printf("%d\n",(n+i-1)%10);								//��ӡ��ĩ 
		}
		
		for(i=1;i<=2*(row-1);i++){									//���һ�����׿ո� 
			printf(" ");
		}
		temp=n+row-1;
		for(i=1;i<=(row-1)/2;i++){									//���һ��ǰ�벿�� 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=(row+1)/2;i<=row;i++){								//���һ�к�벿�� 
			printf("%d",temp%10);
			temp--;
			if(i!=row) printf(" ");
			else printf("\n");
		}
	}
	else{															//ż���� 
		temp=n;
		for(i=1;i<=(3*row-2)/2;i++){								//��һ��ǰ�벿�� 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=1;i<=(3*row-2)/2;i++){								//��һ�к�벿��
			temp--;
			printf("%d",temp%10);
			if(i!=(3*row-2)/2) printf(" ");
			else printf("\n");
		}
		
		for(i=2;i<=row-1;i++){										//��ӡ�м��� 
			for(j=1;j<=2*(i-1);j++) 								//��ӡ���׿ո� 
				printf(" ");
			printf("%d",(n+i-1)%10);								//��ӡ����
			for(j=1;j<=6*row-4*i-3;j++)								//��ӡ�м�ո� 
				printf(" ");
			printf("%d\n",(n+i-1)%10);								//��ӡ��ĩ 
		}
		
		for(i=1;i<=2*(row-1);i++){									//���һ�����׿ո� 
			printf(" ");
		}
		temp=n+row-1;
		for(i=1;i<=row/2;i++){										//���һ��ǰ�벿�� 
			printf("%d ",temp%10);
			temp++;
		}
		for(i=1;i<=row/2;i++){										//���һ�к�벿��
			temp--;
			printf("%d",temp%10);
			if(i!=row/2) printf(" ");
			else printf("\n");
		}
	}
} 
