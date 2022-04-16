#include <stdio.h> 
#include <math.h>
int main(){
	int h,min;
	float angle;
	scanf("%d%d",&h,&min);
	
	angle=fabs(h*30+min*0.5-min*6);
	if (angle>=180)
		angle=360-angle;
		
	if (min<=9)
		printf("At %d:0%d the angle is %.1f degrees.\n",h,min,angle);
	else 
		printf("At %d:%d the angle is %.1f degrees.\n",h,min,angle);
}
