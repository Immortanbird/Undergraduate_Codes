#include <stdio.h>
#include <string.h>
int max(int a,int b){
	if(a>=b) return a;
	else return b;
}

int main(){
	int n;
	scanf("%d",&n);
	char input[1002];
	int i,j;
	//Debug:for(i=0;i<=n;i++) printf("%s\n",input[i]);
	
	for(j=1;j<=n;j++){
		char string_1[501],string_2[501],op;
		int s,temp;
		
		gets(input);
		for(i=0;i<=499;i++){						//����ַ��� 
			if(input[i]!='+'&&input[i]!='-') string_1[i]=input[i];
			else break;
		}
		op=input[i];
		temp=i+1;
		for(i=i+1;i<=1000;i++){
			if(input[i]!='\0') string_2[i-temp]=input[i];
			else break;
		}
		//Debug:printf("%s\n%s\n",string_1,string_2);
	
		int bit_1,bit_2;							//ȷ��λ�� 
		bit_1=strlen(string_1);
		bit_2=strlen(string_2);
		//Debug:printf("%c\n",input[bit_1+bit_2+1]);
		//Debug:printf("%d\n%d\n",bit_1,bit_2);
		
		int digit_1[500]={0},digit_2[500]={0};		//�ַ�ת���֣���λ��ǰ����λ�ں� 
		for(i=bit_1-1;i>=0;i--){
			digit_1[bit_1-1-i]=string_1[i]-48;
		}
		for(i=bit_2-1;i>=0;i--){
			digit_2[bit_2-1-i]=string_2[i]-48;
		}
		
		int result[501]={0};
		switch(op){
			case '+':{								//�ӷ� 
				for(i=0;i<=max(bit_1,bit_2);i++){
					result[i]=result[i]+digit_1[i]+digit_2[i];
					if(result[i]>9){
						result[i]=result[i]-10;
						result[i+1]=1;
					}
				}
				for(i=500;i>=0;i--){				//��� 
					if(result[i]==0) continue;
					else break;
				}
				while(i>=0){
					printf("%d",result[i]);
					if(i==0) printf("\n");
					i--;
				}
				break;
			}
		
			case '-':{								//����
				s=1;
				for(i=max(bit_1,bit_2)-1;i>=0;i--){
					if(digit_1[i]>digit_2[i]){
						s=0;
						break;
					}
				}
				if(s){								//���Ϊ�� 
					for(i=0;i<=max(bit_1,bit_2);i++){
						result[i]=result[i]+digit_2[i]-digit_1[i];
						if(result[i]<0){
							result[i]=result[i]+10;
							result[i+1]=-1;
						}
					}
					for(i=500;i>=0;i--){				//��� 
						if(result[i]==0) continue;
						else break;
					}
					printf("-");
					while(i>=0){
						printf("%d",result[i]);
						if(i==0) printf("\n");
						i--;
					}
				}
				else{									//���Ϊ�� 
					for(i=0;i<=max(bit_1,bit_2);i++){
						result[i]=result[i]+digit_1[i]-digit_2[i];
						if(result[i]<0){
							result[i]=result[i]+10;
							result[i+1]=-1;
						}
					}
					for(i=500;i>=0;i--){				//��� 
						if(result[i]==0) continue;
						else break;
					}
					while(i>=0){
						printf("%d",result[i]);
						if(i==0) printf("\n");
						i--;
					}
				}
				break;
			}
		}
	}
}
