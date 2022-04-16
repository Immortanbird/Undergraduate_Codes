/* 
数制转换： 
输入2个数字，数字的进制不定。

需要找出两个数字在什么进制下值相同 
*/ 

#include<stdio.h>
#include<string.h>

long convert(int base, int *str, int len)
{
	//convert str to dec long digit in specifical base
	long x = 0;
	int i;
	
	for(i=0;i<len;i++){
		x = x*base + str[i];
	}
	return x;
}

int def_base(char *str, int *dig, int len)
{
	//output min base and dec digit array of str
	int cbase = 2;
	int i=0;
	
	//printf("\n%s has len: %d\n",str,len);
	for(i=0;i<len;i++) 
	{
		if( str[i]>='0' && str[i]<='9' ){
			dig[i] = (int)str[i] - 48;
			cbase = cbase < dig[i]+1 ? dig[i]+1 : cbase;	//当前数字+1，就是进制 
			continue;
		}
		if( str[i]>='A' && str[i]<='Z' ){
			dig[i] = (int)str[i] - 65;
			cbase = cbase < dig[i]+1 ? dig[i]+1 : cbase;		
			continue;
		}		
		if( str[i]>='a' && str[i]<='z' ){
			dig[i] = (int)str[i] - 97;
			cbase = cbase < dig[i]+1 ? dig[i]+1 : cbase;			
			continue;
		}
		if( str[i] == '\0' ) {
			break;
		}
	}
	
	//printf("\n%s has min base: %d",str,cbase);
	return cbase;
	
}

int main()
{ 
	char str_a[50], str_b[50];
	int dec_a[50], dec_b[50];
	long dig_a, dig_b;
	
	gets(str_a);
	gets(str_b);
	
	int min_base_a, min_base_b, len_a, len_b;
	len_a = strlen(str_a);
	len_b = strlen(str_b);
	min_base_a = def_base(str_a, dec_a, len_a);
	min_base_b = def_base(str_b, dec_b, len_b);
	
	int base;
	base = min_base_a < min_base_b ? min_base_a : min_base_b;
	
	while(base<=36){
		dig_a = convert(base, dec_a, len_a);
		dig_b = convert(base, dec_b, len_b);
		if(dig_a == dig_b){
			printf( "%s is equal to %s in base %d.", str_a, str_b, base);
			return 0;
		}
		base++;
	}
	printf( "%s is not equal to %s in any base.", str_a, str_b);
} 
