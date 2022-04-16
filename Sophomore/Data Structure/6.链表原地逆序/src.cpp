/* 
* 请编写函数 void inverse( LinkList )，实现单链表的原地置逆。即利用原来的结点将线性表：L =（a1, a2, …… , an）变换为：L =（ an,  …… , a2, a1）
* 说明：本题目为经典的单链表算法设计题目，预设代码中仅用到了C++中的个别东西，但没有采用面向对象的编程方式。
*/

/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct node
{   ElemType    data;
    struct node * next;
} NODE;
typedef NODE * LinkList;

void output( LinkList );
void change( int, int, NODE * );
LinkList createList( ElemType );
void inverse( LinkList ); 

LinkList createList( ElemType finish )	//finish：数据结束标记 
{
    ElemType x;
    NODE *newNode; 
    LinkList first = new NODE;   // 建立头结点
    first->next = NULL;
    first->data = finish;
    cin >> x;	      			// 约定以finish结束连续输入
    while ( x != finish )
	{
        newNode = new NODE;      // 建立新结点
       	newNode->data = x;
       	newNode->next = first->next; // ①
      	first->next = newNode;       // ②
		cin >> x;
    }
    return first;
}

void output( LinkList head )
{   cout << "List:";
	while ( head->next != NULL )
	{   cout << head->next->data << ",";
		head = head->next;
	}
	cout << endl;
}

int main(int argc, char** argv) 
{
	LinkList head;

	head = createList( -1 );
	output( head );
	inverse( head );
	output( head );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

void inverse ( LinkList head ) {
	LinkList Head = head->next;
	LinkList p,q;
    p = NULL;

	while ( Head ) {
		q = Head;
        Head = Head->next;

        q->next = p;
        p = q;
	}
    head->next = p;

	return;
}