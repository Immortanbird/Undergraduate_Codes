/* 
* 排序二叉树是指左子树的所有节点的值均小于它根节点的值，右子树的所有节点的值均大于它根节点的值。
* 
* 输入：输入有一行，表示若干个要排序的数，输入0时停止
* 
* 输出：
*   二叉树的凹入表示
*   和二叉树的中序遍历序列
* 
* sample：
* input:
*   56 78 34 89 12 35 67 77 22 57 0
* output:
*         12
*             22
*     34
*         35
* 56
*             57
*         67
*             77
*     78
*         89
* 12 22 34 35 56 57 67 77 78 89
*/

#include<iostream>

using namespace std;

typedef struct NODE {
    int num;
    int depth;
    struct NODE *Leftchild;
    struct NODE *Rightchild;
}Treenode;

void ProcessNode ( Treenode *p , int n ) {
    p->num = n;
    p->depth = 0;
    p->Leftchild = NULL;
    p->Rightchild = NULL;

    return;
}

void InsertNode ( Treenode *root , Treenode *p ) {
    for ( int i=1 ; ; i++ ) {
        if ( p->num < root->num ){
            if ( root->Leftchild ) 
                root = root->Leftchild;
            else {
                root->Leftchild = p;
                p->depth = i;
                return;
            }
        }
        else {
            if ( root->Rightchild ) 
                root = root->Rightchild;
            else {
                root->Rightchild = p;
                p->depth = i;
                return;
            }
        }
    }

    return;
}

void RetractiveDisplay ( Treenode *root ) {
    if ( root->Leftchild ) 
        RetractiveDisplay ( root->Leftchild );

    for ( int i=0 ; i<4*root->depth ; i++ ) 
            cout << ' ';
    cout << root->num << endl;
    
    if ( root->Rightchild ) 
        RetractiveDisplay ( root->Rightchild );

    return;
}

void InOrderTraverse ( Treenode *root ) {
    if ( root->Leftchild ) 
        InOrderTraverse ( root->Leftchild );

    cout << ' ' << root->num;

    if ( root->Rightchild ) 
        InOrderTraverse ( root->Rightchild );

    return;
}

int main () {
    int temp;
    cin >> temp;
    Treenode *Root = new Treenode;
    ProcessNode ( Root , temp );

    cin >> temp;
    while ( temp ) {
        Treenode *q = new Treenode;
        ProcessNode ( q , temp );
        InsertNode ( Root , q );
        cin >> temp;
    }
    
    RetractiveDisplay ( Root );
	cout << endl;
    InOrderTraverse ( Root );
	cout << endl;

    return 0;
}