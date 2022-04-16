/*
* 编写程序实现二叉树的如下操作：
*   1) 建立二叉链表
*   2) 二叉树的先序、中序、后序遍历
*   3) 求二叉树的叶子结点个数
*   4) 将二叉树中所有结点的左、右子树相互交换
* 
* 输入：
*   按完全二叉树的层次关系给出二叉树的遍历序列（#表示虚结点，数据结点为单一字符）。
* 
* 输出：
*   二叉树的凹入表示
*   二叉树的先序序列、中序序列、后序序列
*   二叉树叶子结点个数
*   左、右子树相互交换后的二叉树的凹入表示
*   左、右子树相互交换后的二叉树的先序序列、中序序列、后序序列。
* 
* 说明：
*   在输出凹入表示的二叉树时，先输出根结点，然后依次输出左右子树，上下层结点之间相隔 3 个空格。
*/

#include<iostream>
#include<queue>

using namespace std;

int sum = 0;

typedef struct NODE {
    char x;
    struct NODE *Leftchild;
    struct NODE *Rightchild;
}Node;

void CreateBinTree ( Node *root ) {
    Node *q;
    char temp = getchar();
    
    queue <Node*> que;

    while ( temp != '\n' ) {
        if ( root->x == 0 ) {
            root->x = temp;
            que.push ( root );
            temp = getchar();
            continue;
        }

        if ( temp == '#' ) 
            temp = 0;

        q = (Node *) malloc ( sizeof(Node) );
        q->x = temp;
        q->Leftchild = NULL;
        q->Rightchild = NULL;
    
        if ( que.front()->Leftchild == NULL ) {
            que.front()->Leftchild = q;
            if ( q )
                que.push(q);
            temp = getchar();
            continue;
        }
        
        if ( que.front()->Rightchild == NULL ) {
            que.front()->Rightchild = q;
            if ( q ) 
                que.push(q);
            que.pop();
            temp = getchar();
            continue;
        }
    }

    return;
}

void aorubiaoshi ( Node* root , int depth ) {
    if ( root->x ) {
        for ( int i=0 ; i<4*depth ; i++ ) 
            cout << ' ';
        cout << root ->x << endl;
    }
    else 
        return;

    if ( root->Leftchild ) 
        aorubiaoshi ( root->Leftchild , depth+1 );
    
    if ( root->Rightchild ) 
        aorubiaoshi ( root->Rightchild , depth+1 );

    return;
}

void PreOrderTraverse ( Node* root ) {
    if ( root->x == 0 ) 
        return;
    
    cout << root->x;

    if ( root->Leftchild ) 
        PreOrderTraverse ( root->Leftchild );

    if ( root->Rightchild ) 
        PreOrderTraverse ( root->Rightchild );

    return;
}

void InOrderTraverse ( Node* root ) {
    if ( root->x == 0 ) 
        return;
    
    if ( root->Leftchild ) 
        InOrderTraverse ( root->Leftchild );

    cout << root->x;

    if ( root->Rightchild ) 
        InOrderTraverse ( root->Rightchild );

    return;
}

void PostOrderTraverse ( Node* root ) {
    if ( root->x == 0 ) 
        return;
    
    if ( root->Leftchild ) 
        PostOrderTraverse ( root->Leftchild );
    
    if ( root->Rightchild ) 
        PostOrderTraverse ( root->Rightchild );
     
    cout << root->x;

    return;
}

void CountLeaf ( Node* root ) {
    if ( root->x == 0 ) 
        return;

    if ( (root->Leftchild==NULL || root->Leftchild->x==0) && (root->Rightchild==NULL || root->Rightchild->x==0) ) {
        sum ++;
        return;
    }
    
    if ( root->Leftchild ) 
        CountLeaf ( root->Leftchild );
    
    if ( root->Rightchild ) 
        CountLeaf ( root->Rightchild );

    return;
}

void SwapBinTree ( Node* root ) {
    Node* temp = root->Leftchild;
    root->Leftchild = root->Rightchild;
    root->Rightchild = temp;

    if ( root->Leftchild ) 
        SwapBinTree ( root->Leftchild );

    if ( root->Rightchild ) 
        SwapBinTree ( root->Rightchild );

    return;
}

int main () {
    Node *Root = (Node *) malloc ( sizeof(Node) );
    Root->x = 0;
    Root->Leftchild = NULL;
    Root->Rightchild = NULL;

    CreateBinTree ( Root );

    cout << "BiTree" << endl;
    aorubiaoshi ( Root , 0 );

    cout << "pre_sequence  : ";
    PreOrderTraverse ( Root );
    cout << endl;

    cout << "in_sequence   : ";
    InOrderTraverse ( Root );
    cout << endl;

    cout << "post_sequence : ";
    PostOrderTraverse ( Root );
    cout << endl;

    cout << "Number of leaf: ";
    CountLeaf ( Root );
    cout << sum << endl;

    cout << "BiTree swapped" << endl;
    SwapBinTree ( Root );
    aorubiaoshi ( Root , 0 );

    cout << "pre_sequence  : ";
    PreOrderTraverse ( Root );
    cout << endl;

    cout << "in_sequence   : ";
    InOrderTraverse ( Root );
    cout << endl;

    cout << "post_sequence : ";
    PostOrderTraverse ( Root );
    cout << endl;
    
    return 0;
}