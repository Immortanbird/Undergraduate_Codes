/* 
* 请判断：指定的序列能否仅由 入栈 和 出栈 操作得到。
* 
* 输入：
*   有若干组数据输入
*   每组数据中，第一行为两个个整数n和m。n表示需要依次从1~n入栈，m表示这组数据有m个出栈序列需要判断，当n=0且m=0时停止。
*   接下来有行，每行表示一个出栈序列
* 
* 输出：
*   对每一个出栈序列，如果能正常出栈，则输出 Yes，否则输出 No。
* 
* sample：
*   input:
*       5 2
*       1 2 3 4 5
*       5 4 1 2 3
*       6 1
*       6 5 4 3 2 1
*       0 0
*   output:
*       Yes
*       No
*       
*       Yes
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack {
    int *top;
    int *base;
}Stack;

typedef struct NODE {
    int x;
    struct NODE *next;
}Sequence;

int n,m;
Stack stk;

void InitializeStack () {
    memset ( stk.base , 0 , 100*sizeof(int) ) ;
    stk.top = stk.base;

    return;
}

void Push ( int i ) {
    stk.top++;
    *stk.top = i;
    
    return;
}

void Pop () {
    stk.top--;

    return;
}

int main () {
    stk.base = (int *) malloc ( 100*sizeof(int) );
    
    scanf ( "%d%d" , &n , &m );

    while ( n && m ) {
        while ( m-- ) {
            InitializeStack ();
            Sequence *head,*p,*q;
            head = (Sequence *) malloc ( sizeof(Sequence) );
            p = head;
            int tmp;

            for ( int i=0 ; i<n ; i++ ){
                q = (Sequence *) malloc ( sizeof(Sequence) );
                scanf ( "%d" , &tmp );
                q->x = tmp;
                q->next = NULL;
                p->next = q;
                p = q;
            }

            tmp = 1;
            Sequence *temp = head;
            head = head->next;
            free ( temp );

            while ( head && tmp<=n ) {
                if ( tmp == head->x ) {
                    Sequence *temp = head;
                    head = head->next;
                    free ( temp );
                    tmp++;
                }
                else if ( *stk.top == head->x ) {
                    Pop ();
                    Sequence *temp = head;
                    head = head->next;
                    free ( temp );
                }
                else {
                    Push ( tmp );
                    tmp++;
                }
            }

            if ( stk.top != stk.base ) {
                while ( stk.top != stk.base && *stk.top == head->x ) {
                    stk.top--;
                    Sequence *temp;
                    temp = head;
                    head = head->next;
                    free ( temp );
                }
            }

            if ( head )
                printf ( "No\n");
            else 
                printf ( "Yes\n");
        }

        scanf ( "%d%d" , &n , &m );
        if ( m && n ) 
            printf ( "\n" );
    }

    return 0;
}
/*
5 2 
1 2 3 4 5 
5 4 1 2 3 
6 2 
6 5 4 3 2 1 
3 2 5 6 4 1 
0 0 
*/