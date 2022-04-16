/* 
* 对于任意的真分数 N/M （ 0 < N < M ），均可以求出对应的小数。如果采用链表存储各位小数，对于循环节采用循环链表表示，则所有分数均可以表示为如下链表形式：
* head->null node->...
* 
* 输入： N M
* 输出： 整个循环节
* 
* 要求：编写一个尽可能高效的查找循环节起始点的函数： NODE * find( NODE * head, int * n ) 。函数的返回值为循环节的起点（即图中的指针p），n为循环节的长度。
* 
* 说明：提交程序时请同时提交将分数转换为小数的函数 change( int n, int m, NODE * head ) （前面题目中已经编写）。
*/

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{   int         data;
    struct node * next;
} NODE;

NODE * find( NODE * , int * );
void outputring( NODE * );
void change( int , int , NODE * );
void outputring( NODE * pring )
{	NODE * p;
	p = pring;
	if ( p == NULL )
		printf("NULL");
	else
		do	{	printf("%d", p->data);
			p = p->next;
		} while ( p != pring );
	printf("\n");
	return;
}

int main()
{   int n, m;
	NODE * head, * pring;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;

	change( n, m, head );
	pring = find( head, &n );
	printf("ring=%d\n", n);
	outputring( pring );

	return 0;
}

/* Here is waiting for you.
void change( int n, int m, NODE * head )
{ 
}

NODE * find( NODE * head, int * n )
{
}
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

NODE *Start = NULL;

NODE * find ( NODE * head, int * n ) {
	if ( Start ) {
		NODE *temp = Start->next;
		int count = 1;
		while ( temp != Start ) {
			count++;
			temp = temp->next;
		}
		*n = count;
	}
	else 
		*n = 0;
	
	return Start;
}

void change( int n, int m, NODE * head ) {
    NODE *p,*q;
	int div = n*10;
	int rem[5000];
	int len = 0;

	p = head;

	while ( div ){
		q = ( NODE * ) malloc ( sizeof(NODE) );
		q->data = div/m;
		q->next = NULL;
		p->next = q;

		for ( int i=0 ; i<len ; i++ ) {
			if ( rem[i] == div ) {
				q = head->next;
				while ( i-- ) 
					q = q->next;
				p->next = q;
				Start = q;
				return;
			}
		}

		p = q;

		rem[len] = div;
		len++;
		div = (div%m)*10;
	}

    return;
}