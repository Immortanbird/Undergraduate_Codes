/* 
* 程序输入一个字符串（只包含小写字母），请按照字符的输入顺序建立平衡二叉排序树，并分别输出二叉树的先序序列、中序序列和后序序列，最后输出该二叉树向左旋转 90 度后的结构。
* 
* 例如：向左旋转 90 度后，以每层向里缩进 4 个空格的方式输出，输出结果为：
* 
*         i
*     g
*         f
* a
*         d
*     c
*         b
* 
* 输入：agxnzyimk
* 
* 输出：
*   Preorder: xigamknzy
*   Inorder: agikmnxyz
*   Postorder: agknmiyzx
*   Tree:
*       z
*           y
*   x
*               n
*           m
*               k
*       i
*           g
*               a
*/

#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct NODE {
    char data;
    int factor;
    struct NODE *Leftchild;
    struct NODE *Rightchild;
}Treenode;

void InitializeNode ( Treenode *p , char x ) {
    p->data = x;
    p->factor = 0;
    p->Leftchild = NULL;
    p->Rightchild = NULL;

    return;
}

void R_Rotate ( Treenode **root ) {
    Treenode *temp = (*root)->Leftchild;
    (*root)->Leftchild = temp->Rightchild;
    temp->Rightchild = *root;
    *root = temp;

    return;
}

void L_Rotate ( Treenode **root ) {
    Treenode *temp = (*root)->Rightchild;
    (*root)->Rightchild = temp->Leftchild;
    temp->Leftchild = *root;
    *root = temp;

    return;
}

void Rightbalance ( Treenode **root ) {
    Treenode *Rchild = (*root)->Rightchild;
    Treenode *rd = Rchild->Leftchild;

    switch ( Rchild->factor ) {
        case 1:
            (*root)->factor = Rchild->factor = 0;
            L_Rotate ( root );
            break;
        case -1:
            switch ( rd->factor ) {
                case -1:
                    (*root)->factor = 0;
                    Rchild->factor = 1;
                    break;
                case 0:
                    (*root)->factor = Rchild->factor = 0;
                    break;
                case 1:
                    (*root)->factor = -1;
                    Rchild->factor = 0;
                    break;
            }
            rd->factor = 0;
            R_Rotate ( &(*root)->Rightchild );
            L_Rotate ( root );
            break;
    }

    return;
}

void Leftbalance ( Treenode **root ) {
    Treenode *Lchild = (*root)->Leftchild;
    Treenode *rd = Lchild->Rightchild;

    switch ( Lchild->factor ) {
        case 1:
            switch ( rd->factor ) {
                case -1:
                    (*root)->factor = 1;
                    Lchild->factor = 0;
                    break;
                case 0:
                    (*root)->factor = Lchild->factor = 0;
                    break;
                case 1:
                    (*root)->factor = 0;
                    Lchild->factor = -1;
                    break;
            }
            rd->factor = 0;
            L_Rotate ( &(*root)->Leftchild );
            R_Rotate ( root );
            break;
        case -1:
            (*root)->factor = Lchild->factor = 0;
            R_Rotate ( root );
            break;
    }
    
    return;
}

void InsertNode ( Treenode **root , char x , bool *taller ) {
    if ( (*root) == NULL ) {
        (*root) = (Treenode*) malloc ( sizeof(Treenode) );
        InitializeNode ( *root , x );
        *taller = true;
    }
    else if ( x < (*root)->data ) {
        InsertNode ( &(*root)->Leftchild , x , taller );
        if ( *taller ) 
            switch ( (*root)->factor ) {
                case 1:
                    (*root)->factor--;
                    *taller = false;
                    break;
                case 0:
                    (*root)->factor--;
                    *taller = true;
                    break;
                case -1:
                    Leftbalance ( root );
                    *taller = false;
                    break;
            }
    }
    else if ( x > (*root)->data ) {
        InsertNode ( &(*root)->Rightchild , x , taller );
        if ( *taller )
            switch ( (*root)->factor ) {
                case -1:
                    (*root)->factor++;
                    *taller = false;
                    break;
                case 0:
                    (*root)->factor++;
                    *taller = true;
                    break;
                case 1:
                    Rightbalance ( root );
                    *taller = false;
                    break;
            }
    }

    return;
}

void PreOrderTraverse ( Treenode *root ) {
    cout << root->data;

    if ( root->Leftchild ) 
        PreOrderTraverse ( root->Leftchild );
    
    if ( root->Rightchild ) 
        PreOrderTraverse ( root->Rightchild );
    
    return;
}

void InOrderTraverse ( Treenode *root ) {
    if ( root->Leftchild ) 
        InOrderTraverse ( root->Leftchild );
    
    cout << root->data;

    if ( root->Rightchild ) 
        InOrderTraverse ( root->Rightchild );
    
    return;
}

void PostOrderTraverse ( Treenode *root ) {
    if ( root->Leftchild ) 
        PostOrderTraverse ( root->Leftchild );
    
    if ( root->Rightchild ) 
        PostOrderTraverse ( root->Rightchild );

    cout << root->data;

    return;
}

void RetractiveDisplay ( Treenode *root , int i ) {
    if ( root->Rightchild ) 
        RetractiveDisplay ( root->Rightchild , i+4 );    
    
    for ( int j=0 ; j<i ; j++ )
        cout << ' ';
    cout << root->data << endl;

    if ( root->Leftchild ) 
        RetractiveDisplay ( root->Leftchild , i+4 );

    return;
}

int main () {
    char temp;
    Treenode *Root = NULL;
    bool taller;

    while ( (temp = getchar()) != '\n' ) 
        InsertNode ( &Root , temp , &taller );
    
    cout << "Preorder: ";
    PreOrderTraverse ( Root );
    cout << endl;
    cout << "Inorder: ";
    InOrderTraverse ( Root );
    cout << endl;
    cout << "Postorder: ";
    PostOrderTraverse ( Root );
    cout << endl;
    cout << "Tree:" << endl;
    RetractiveDisplay ( Root , 0 );

    return 0;
}