#include <stdio.h>
int gcd(int x,int y){
	if(x%y==0) return y;
	else return gcd(y,x%y);
}

int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	if(a<b){
		int temp;
		temp=a;
		a=b;
		b=temp;
	}
	printf("%d\n",gcd(a,b));
}
