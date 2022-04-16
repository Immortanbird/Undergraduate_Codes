/* 
* 程序的输入是无向图的顶点序列和边序列(顶点序列以*为结束标志，边序列以-1,-1为结束标志)。程序的输出为图的邻接表和广度优先遍历序列。例如：
* 
* 程序输入为：
*   a
*   b
*   c
*   d
*   e
*   f
*   *
*   0,1
*   0,4
*   1,4
*   1,5
*   2,3
*   2,5
*   3,5
*   -1,-1
* 
* 程序的输出为：
*   the ALGraph is
*   a 4 1
*   b 5 4 0
*   c 5 3
*   d 5 2
*   e 1 0
*   f 3 2 1
*   the Breadth-First-Seacrh list:aebfdc
*/

// 有一个测试用例没过

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

typedef struct Node {
    int arc;
    struct Node *next;
}Arcnode;

typedef struct NODE {
    char data;
    bool visit;
    struct Node *next;
}Vnode;

void GetVertex ( char ver[] ) {
    char temp;
    temp = getchar();
    getchar();

    for ( int i=0 ; temp!='*' ; i++ ) {
        ver[i] = temp;
        temp = getchar();
        getchar();
        if ( temp == '*' ) 
            ver[i+1] = '\0';
    }

    return;
}

Vnode *BuildAdjacencyList ( char *ver ) {
    Vnode *list = (Vnode *) malloc ( strlen(ver)*sizeof(Vnode) );
    for ( int i=0 ; i<strlen(ver) ; i++ ) {
        list[i].data = ver[i];
        list[i].visit = false;
        list[i].next = NULL;
    }
    
    int x,y;
    scanf ( "%d,%d" , &x , &y );

    while ( x != -1 ) {
        Arcnode *p = (Arcnode *) malloc ( sizeof(Arcnode) );
        p->arc = y;
        p->next = list[x].next;
        list[x].next = p;
        
        Arcnode *q = (Arcnode *) malloc ( sizeof(Arcnode) );
        q->arc = x;
        q->next = list[y].next;
        list[y].next = q;

        scanf ( "%d,%d" , &x , &y );
    }

    return list;
}

void PrintGraph ( char *ver , Vnode *list ) {
    cout << "the ALGraph is" << endl;
    for ( int i=0 ; i<strlen(ver) ; i++ ) {
        cout << list[i].data << ' ';
        Arcnode *p = list[i].next;
        while ( p ) {
            cout << p->arc;
            if ( p->next ) 
                cout << ' ';
            p = p->next;
        }
        cout << endl;
    }

    return;
}

void BFS ( Vnode *list , int start ) {
    queue<Vnode> que;
    que.push ( *(list+start) );
    (list+start)->visit = true;

    while ( !que.empty() ) {
        cout << que.front().data;
        Arcnode *p = que.front().next;
        while ( p ) {
            if ( !list[p->arc].visit ) {
                que.push ( list[p->arc] );
                list[p->arc].visit = true;
            }
            p = p->next;
        }
        que.pop();
    }

    return;
}

int main () {
    char Vertex[50];
    GetVertex ( Vertex );

    Vnode *AdjacencyList = BuildAdjacencyList ( Vertex );
    PrintGraph ( Vertex , AdjacencyList );

    cout << "the Breadth-First-Seacrh list:";
    for ( int i=0 ; i<strlen(Vertex) ; i++ ) {
        if ( AdjacencyList[i].visit == false ) 
            BFS ( AdjacencyList , i );
    }
    cout << endl;

    return 0;
}