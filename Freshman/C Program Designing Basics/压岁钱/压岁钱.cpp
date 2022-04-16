#include <stdio.h>
#include <string.h>
int main(){
	int N;
	scanf("%d",&N);
	
	char order[N][15],name[N][15],to[90][15];
	int money[N],give[N];
	int temp[N],i,j,k,flag=0;
	char*p[N];
	
	for(i=0;i<N;i++){
		p[i]=order[i];
	}
	
	for(i=0;i<N;i++){
		scanf("%s",order[i]);
	}
	for(i=0;i<N;i++){
		scanf("%s",name[i]);
		scanf("%d",&money[i]);
		scanf("%d",&give[i]);
		for(j=0;j<give[i];j++){
			scanf("%s",to[flag]);
			flag++;
		}
	}
	
	flag=0;
	for(i=0;i<N;i++){
		if(money[i]==0||give[i]==0){
			temp[i]=0;
			continue;
		}
		temp[i]=money[i]/give[i];
		money[i]=-give[i]*temp[i];
	}
	
	for(i=0;i<N;i++){
		for(j=0;j<give[i];j++){
			//search for receiver
			for(k=0;k<N;k++){
				if(strcmp(to[flag],name[k])==0) break;
			}
			money[k]+=temp[i];
			flag++;
		}
	}
	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(strcmp(p[i],name[j])==0) break;
		}
		printf("%s %d\n",name[j],money[j]);
	}
}
