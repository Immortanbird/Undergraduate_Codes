#include <stdio.h>
int judge(int year){
	if((year%4==0&&year%100!=0)||year%400==0) return 1;
	else return 0;
}

int m(int year, int month){
	int mon[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(judge(year)==1){
		mon[1]=29;
	}
	return mon[month-1];
}

int main(){
	int year,month,day,n;
	scanf("%d%d%d%d",&year,&month,&day,&n);
	n+=day-1;
	day=1;
	
	while(n>=m(year,month)){
		n-=m(year,month);
		month++;
		if(month>12){
			year++;
			month=1;
		}
	}
	day+=n;
	
	printf("%d.%d.%d\n",year,month,day);
}
