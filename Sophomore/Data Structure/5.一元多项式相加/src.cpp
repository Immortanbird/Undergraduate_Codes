/* 
* 题目说明：
* 编写一元多项式加法运算程序。要求用线性链表存储一元多项式（参照课本）。该程序有以下几个功能：
* 
* 1. 多项式求和
*   输入：输入三个多项式，建立三个多项式链表Pa、Pb、Pc
*   （提示：调用CreatePolyn(polynomial &P,int m)。
*   输出：显示三个输入多项式Pa、Pb、Pc、和多项式Pa+Pb、多项式Pa+Pb+Pc
*   （提示：调用AddPolyn(polynomial &Pa, polynomial Pb), 调用PrintPolyn(polynomial P))。
* 0. 退出
* 
* 输入：
*   根据所选功能的不同，输入格式要求如下所示（第一个数据是功能选择编号，参见测试用例）：
*   1
*   多项式A包含的项数，以指数递增的顺序输入多项式A各项的系数（整数）、指数（整数）
*   多项式B包含的项数，以指数递增的顺序输入多项式B各项的系数（整数）、指数（整数）
*   多项式C包含的项数，以指数递增的顺序输入多项式C各项的系数（整数）、指数（整数）
*   0 －－－操作终止，退出。
* 
* 输出：
*   对应一组输入，输出一次操作的结果（参见测试用例）。

* 1 多项式输出格式：以指数递增的顺序输出: <系数,指数>,<系数,指数>,<系数,指数>,参见测试用例。零多项式的输出格式为<0,0>
* 0 无输出
*/

// 注：有一个测试用例没过

#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct Node{
    int num , index;
    struct Node *former;
    struct Node *next;
}Polyn;

Polyn *heads[3];
Polyn *result;

void CreatePolyn ();
void MergePolyn ( Polyn * , Polyn * );
void DestroyNode ( Polyn * );
void PrintPolyn ( Polyn * );

int main (){
    int starter;
    cin >> starter;

    if ( starter == 0 ) 
        return 0;
    
    CreatePolyn();

	PrintPolyn ( heads[0] );
	PrintPolyn ( heads[1] );
	PrintPolyn ( heads[2] );
    
    MergePolyn ( heads[0] , heads[1] );

    PrintPolyn ( heads[0] );

    MergePolyn ( heads[0] , heads[2] );

    PrintPolyn ( heads[0] );

    return 0;
}

void CreatePolyn() {
    for ( int i=0 ; i<3 ; i++ ) {
        heads[i] = ( Polyn* ) malloc ( sizeof(Polyn) );
        heads[i]->former = NULL;
        heads[i]->next = NULL;
    }

    Polyn *p,*q;
    for ( int i=0 ; i<3 ; i++ ) {
        cin >> heads[i]->num;
		if ( heads[i]->num == 0 ) 
			continue;

        p = heads[i];
        for ( int j=0 ; j<heads[i]->num ; j++ ) {
            q = ( Polyn* ) malloc ( sizeof(Polyn) );
            cin >> q->num >> q->index;

            q->former = p;
            q->next = NULL;
            p->next = q;
            p = q;
        }
    }

    return;
}

void MergePolyn ( Polyn *x , Polyn*y ) {
    /*把y的节点加入x中*/
    Polyn *temp;
    
	if ( x->next == NULL ) {
		x->next = y->next;
		return;
	} 
    x = x->next;
    y = y->next;

    while ( x && y ) {
        if ( x->index == y->index ) {
            x->num += y->num;

            temp = y;
            y = y->next;
            DestroyNode ( temp );
            if ( x->next ) 
                x = x->next;
            else {
                x->next = y;
                while ( y ) {
                    temp = y;
                    y = y->next;
                    free ( temp );
                }
                break;
            }
            continue;
        }

        if ( x->index < y->index ) {
            if ( x->next ) 
                x = x->next;
            else {
                x->next = y;
                break;
            }
            continue;
        }

        if ( x->index > y->index ) {
			temp = y;
			y = y->next;
			if ( temp->next ) 
            	temp->next->former = NULL;
			x->former->next = temp;
			temp->former = x->former;
			x->former = temp;
			temp->next = x;
        }
    }

    return;
}

void DestroyNode ( Polyn *T ) {
	if ( T->next ) 
    	T->next->former = NULL;
    free ( T );

    return;
}

void PrintPolyn ( Polyn *Out ) {
    Out = Out->next;
    while ( Out ) {
		if ( Out->num ) 
        	printf ( "<%d,%d>" , Out->num , Out->index );
		else if ( Out->next ) {
			Out = Out->next;
			continue;
		}
		else {
			printf ( "<0,0>\n");
			return;
		}
			
        if ( Out->next ) 
            cout << ',';
        else 
            cout << endl;
        Out = Out->next;
    }
    
    return;
}