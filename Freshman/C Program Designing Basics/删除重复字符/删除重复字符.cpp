#include <stdio.h>
#include <string.h>
int main(){
	char str[101];
	scanf("%s",str);
	
	char test[101]={'\0'};
	int i,j,k=0;
	for(i=0;i<strlen(str);i++){
		for(j=0;j<=i;j++){
			if(str[i]==test[j]) goto next;
		}
		test[k]=str[i];
		k++;
		next:continue;
	}
	printf("%s\n",test);
}
