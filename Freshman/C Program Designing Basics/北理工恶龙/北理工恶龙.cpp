#include <stdio.h>
int main(){
	int dragon,warrior,i,j,temp,s=0;
	scanf("%d%d",&dragon,&warrior);
	
	int head[dragon],height[warrior];
	for(i=0;i<dragon;i++) scanf("%d",&head[i]);
	for(i=0;i<warrior;i++) scanf("%d",&height[i]);
	
	if(warrior<dragon){
		printf("bit is doomed!\n");
		return 0;
	}
	
	for(i=0;i<dragon;i++){
		for(j=0;j<dragon-1;j++){
			if(head[j]>head[j+1]){
				temp=head[j];
				head[j]=head[j+1];
				head[j+1]=temp;
			}
		}
	}
	for(i=0;i<warrior;i++){
		for(j=0;j<warrior-1;j++){
			if(height[j]>height[j+1]){
				temp=height[j];
				height[j]=height[j+1];
				height[j+1]=temp;
			}
		}
	}
	
	temp=0;
	for(i=0;i<dragon;i++){
		for(j=temp;j<warrior;j++){
			if(height[j]>=head[i]){
				s+=height[j];
				temp=j+1;
				break;
			}
		}
		if(j==warrior){
			printf("bit is doomed!\n");
			return 0;
		}
	}
	printf("%d\n",s);
}
