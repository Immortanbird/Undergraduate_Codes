/* 
* Huffman编码是通信系统中常用的一种不等长编码，它的特点是：能够使编码之后的电文长度最短。
* 
* 输入：
*   第一行为要编码的符号数量n
*   第二行～第n+1行为每个符号出现的频率
* 
* 输出：
*   对应哈夫曼树的带权路径长度WPL
*/

#include<iostream>
#include<cstdlib>
#include<algorithm>

using namespace std;

typedef struct NODE {
    int Weight;
    struct NODE *Leftchild;
    struct NODE *Rigthchild;
}Node;

int sum = 0;

bool cmp ( Node x , Node y ) {
    return x.Weight < y.Weight;
}

Node *CreateHuffmanTree ( int *W , int n ) {
    Node *que = (Node *) malloc ( 2*n*sizeof(Node) );
    Node *top, *back;
    top = que;
    back = que;

    for ( int i=0 ; i<n ; i++ ) {
       Node *p = (Node *) malloc ( sizeof(Node) );
       p->Weight = *(W+i);
       p->Leftchild = NULL;
       p->Rigthchild = NULL;
       *back = *p;
       back++;
    }

    Node *p;
    while ( back-top > 1 ) {
        p = (Node *) malloc ( sizeof(Node) );
        p->Weight = 0;

        p->Weight += top->Weight;
        p->Leftchild = top;
        top++;

        p->Weight += top->Weight;
        p->Rigthchild = top;
        top++;

        *back = *p;
        back++;

        sort ( top , back , cmp );
    }

    return top;
}

void WPL ( Node *root , int n ) {
    if ( root->Leftchild == NULL && root->Rigthchild == NULL ) {
        sum += n*root->Weight;
        return;
    }

    if ( root->Leftchild ) 
        WPL ( root->Leftchild , n+1 );
    
    if ( root->Rigthchild ) 
        WPL ( root->Rigthchild , n+1 );
}

int main () {
    int n;
    cin >> n;

    int *W = (int *) malloc ( n*sizeof(int) );
    for ( int i=0 ; i<n ; i++ ) 
        cin >> *(W+i);

    sort ( W , W+n );

    Node *Root = CreateHuffmanTree ( W , n );
    
    WPL ( Root , 0 );

    cout << "WPL=" << sum << endl;

    return 0;
}