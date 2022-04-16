#include <stdio.h>
int main(){
	int kid,flag,i,run=1,count=1,temp;
	scanf("%d%d",&kid,&flag);
	
	if(flag==1){
		printf("The left child is NO %d.\n",kid);
		return 0;
	}
	
	int num[kid];
	for(i=0;i<kid;i++) num[i]=0;

	while(run<kid){
		for(temp=0;temp<kid;temp++){
			if(num[temp]==0){
				if(count==flag){
					num[temp]=1;
					count=1;
					run++;
				}
				else count++;
			}
			else continue;
		}
	}
	
	for(i=0;i<kid;i++){
		if(num[i]==0) printf("The left child is NO %d.\n",i+1);
	}
}
