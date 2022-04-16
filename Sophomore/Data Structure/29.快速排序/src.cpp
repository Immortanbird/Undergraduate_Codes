/* 
* 要求根据给定输入，按照课堂给定的快速排序算法进行排序，输出排序结果和median3的返回值。
* 
* 注：
*   1. cutoff值为5，不足cutoff使用插入排序。
*   2. 输入、输出格式参见测试用例0。
*/

#include<cstdio>  
#include<cstdlib>  
#include<cstring>  
#include<iostream> 
#include<cmath>  
 
using namespace std;  
 
#define MAXSIZE 1000
int a[MAXSIZE];
int b=0;  
  
void Median3(int m[], int i, int j ) {  
    int c=(i+j)/2;  
    if(m[i]>m[c]) swap(m[i],m[c]);  
    
	if(m[i]>m[j]) swap(m[i], m[j]);  
    
	if(m[c]>m[j]) swap(m[c], m[j]);  
    
	swap(m[c],m[j-1]);   
    
	a[b++]=m[j-1];  
}  
   
void insort(int num[],int i,int j){ 
    int k;   
    for(i=2;i<=j;i++) {  
        num[0]=num[i];   
        k=i-1;  
        while(num[0]<num[k]) {     
            num[k+1]=num[k];   
            k=k-1;   
        }         
        num[k+1]=num[0];  
    }  
}  
  
void qsort(int num[],int left,int right) {     
    int i,j,temp;  
    Median3(num,left,right);  
    i=left;  
    j=right-1;  
    int x = num[j];      
    while(1) {  
        while(num[++i]<x){}  
        while(num[--j]>x){}  
        if(i<j) {            
            temp=num[i];  
            num[i]=num[j];  
            num[j]=temp;  
        }  
        else break;  
    }  
    num[right-1]=num[i];
    num[i]=x;          
    if(left+5<=i) 
		qsort(num,left,i-1);   
    else 
		insort(num,left,i-1);  
    
	if(i+5<=right) 
		qsort(num,i+1,right);    
    else 
		insort(num,i+1,right);  
}  
   
int main() {  
    int num[MAXSIZE],i=1,j=1,k=0;  
    
	while((scanf("%d",&num[i])==1)) {  
        getchar();  
        i++;   
    }     
    
    if(i>6)  
        qsort(num,1,i-1);            
    
	else   
        insort(num,1,i-1);  
    printf("After Sorting:\n");  
	 
    while(j<i) {  
        printf("%d ",num[j]);   
        j++;  
    }  
    
    printf("\n");  
    
	printf("Median3 Value:\n");  
    
	if(b>0) {
        while(k<b)
        	printf("%d ",a[k++]);
        printf("\n");  
    }
	
    else printf("none\n");

	return 0;
}