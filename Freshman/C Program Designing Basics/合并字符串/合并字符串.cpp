#include <stdio.h>
#include <string.h>
int main(){
	char a[100],b[100],result[200]={'\0'};
	fgets(a,100,stdin);
	fgets(b,100,stdin);
	
	if(a[0]=='\n'){
		printf("%s",b);
		return 0;
	}
	
	if(b[0]=='\n'){
		printf("%s",a);
		return 0;
	}
	
	int i,j;
	char temp;
	for(i=0;i<strlen(a)-1;i++) result[i]=a[i];
	for(;i<strlen(a)+strlen(b)-2;i++) result[i]=b[i-strlen(a)+1];
	for(i=0;i<strlen(result);i++){
		for(j=0;j<strlen(result)-1;j++){
			if(result[j]>result[j+1]){
				temp=result[j];
				result[j]=result[j+1];
				result[j+1]=temp;
			}
		}
	}
	printf("%s\n",result);
}
