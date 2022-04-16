#include <stdio.h>
#include <stdlib.h>
int gcd(int x,int y){
	if(x<y){
		int temp1;
		temp1=x;
		x=y;
		y=temp1;
	}
	if(x%y==0) return y;
	else return gcd(x,x%y);
}

int main(){
	int x1,x2,y1,y2;
	char op;
	scanf("%d/%d %c %d/%d",&x1,&x2,&op,&y1,&y2);
	
	int r1,r2,temp2;
	switch(op){
		case '+':r1=x1*y2+y1*x2;r2=x2*y2;break;
		case '-':r1=x1*y2-y1*x2;r2=x2*y2;break;
		case '*':r1=x1*y1;r2=x2*y2;break;
		case '/':r1=x1*y2;r2=y1*x2;break;
	}
	
	if(r1==0){
		printf("%d/%d %c %d/%d = 0\n",x1,x2,op,y1,y2);
		return 0;
	}
	
	temp2=gcd(r1,r2);
	r1=r1/temp2;
	r2=r2/temp2;
	
	if(r2==1){
		printf("%d/%d %c %d/%d = %d\n",x1,x2,op,y1,y2,r1);
		return 0;
	}
	if(r2==-1){
		printf("%d/%d %c %d/%d = %d\n",x1,x2,op,y1,y2,-r1);
		return 0;
	}
	if(r1*r2<0) printf("%d/%d %c %d/%d = %d/%d\n",x1,x2,op,y1,y2,-abs(r1),abs(r2));
	else printf("%d/%d %c %d/%d = %d/%d\n",x1,x2,op,y1,y2,r1,r2);
}
