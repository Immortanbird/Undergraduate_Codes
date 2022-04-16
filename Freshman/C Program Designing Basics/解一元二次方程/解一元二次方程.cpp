#include <stdio.h>
#include <math.h>
int main(){
	int a,b,c,delta;
	double x1,x2,x;
	scanf("%d%d%d",&a,&b,&c);
	delta=pow(b,2)-4*a*c;
	
	if (a==0&&b==0){							//无解 
		printf("Input error!\n");
		return(0);
	}
	
	if(a==0){									//一元一次方程 
		x=1.0*-c/b;
		printf("x=%f\n",x);
		return(0);
	}
	
	if (delta<0){								//虚数解 
		if (b==0) {
			x1=sqrt(-delta)/(2*a);
			x2=-x1;
			printf("x1=%fi\nx2=%fi\n",x1,x2);
		}
		else{
			x1=1.0*-b/(2*a);
			x2=sqrt(-delta)/(2*a);
			printf("x1=%f+%fi\nx2=%f%fi\n",x1,x2,x1,-x2);
		}
		return(0);
	}	
	
	if (delta>=0) {								//实数解 
		x1=(-b+sqrt(delta))/(2*a);
		x2=(-b-sqrt(delta))/(2*a);
		if (x1==x2)
			printf("x1=x2=%f\n",x1);
		else
			printf("x1=%f\nx2=%f\n",x1,x2);
		return(0);
	}
} 
