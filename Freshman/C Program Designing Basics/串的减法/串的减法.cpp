#include <stdio.h>
#include <string.h>
int main(){
    char s[81],t[81],u[81]={'\0'};
    scanf("%s%s",s,t);
    
    int i,j,k=0;
    for(i=0;i<strlen(s);i++){
        for(j=0;j<strlen(t);j++){
            if(s[i]==t[j]) goto next;
        }
        u[k]=s[i];
        k++;
        next:continue;
    }
    printf("%s\n",u);
}
