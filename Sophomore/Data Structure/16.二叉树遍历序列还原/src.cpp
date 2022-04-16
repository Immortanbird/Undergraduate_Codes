/* 
* 给出二叉树的中序遍历序列和后序遍历序列，编程还原该二叉树。
* 
* 输入：
*   第1行为二叉树的中序遍历序列
*   第2行为二叉树的后序遍历序列
* 
* 输出：
*   二叉树的按层遍历序列
*/

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

typedef struct NODE {
    char data;
    struct NODE *Leftchild;
    struct NODE *Rightchild;
}Node;

int Search ( char *sequence , char target ) {
    for ( int i=0 ; i<strlen(sequence) ; i++ ) {
        if ( *(sequence+i) == target ) 
            return i;
    }

    return -1;
}

Node *CreateBinTree ( char *Post , char *In , int len ) {
    if ( len == 0 ) 
        return NULL;

    int position = Search ( In , *(Post+len-1) );

    Node *root = new Node;
    root->data = *(In+position);
    root->Leftchild = CreateBinTree ( Post , In , position );
    root->Rightchild = CreateBinTree ( Post+position , In+position+1 , len-position-1 );

    return root;
}

void BFS ( Node *root ) {
    queue <Node *> que;
    que.push ( root );

    while ( !que.empty() ) {
        cout << que.front()->data;
        if ( que.front()->Leftchild ) 
            que.push ( que.front()->Leftchild );
        if ( que.front()->Rightchild ) 
            que.push ( que.front()->Rightchild );
        que.pop();
    }

    cout << endl;
    
    return;
}

int main () {
    char PostSequence[20];
    char InSequence[20];

    gets(InSequence);
    gets(PostSequence);

    Node *Root;

    Root = CreateBinTree ( PostSequence , InSequence , strlen(PostSequence) );

    BFS ( Root );

    return 0;
}