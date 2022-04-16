/* 
* 前缀码：任何一个字符的编码都不是同一字符集中另一个字符的编码的前缀。
* 
* 请编写一个程序，判断输入的n个由1和0组成的编码是否为前缀码。如果这n个编码是前缀码，则输出"YES”；否则输出第一个与前面编码发生矛盾的编码。
* 
* 输入：
*   第1行为n（表示下面有n行编码）
*   第2～n+1行为n个由0或1组成的编码
* 
* 输出：判断结果
* 
* 例如，如果输入：
*   5
*   00
*   01
*   10
*   110
*   111
*   每一个字符均不是其他字符编码的前缀，所以，输出：YES
* 
* 再如，如果输入：
*   5
*   00
*   01
*   10
*   110
*   11
*   编码11与前面的编码110的前缀，所以，输出：11
*/

#include<iostream>

using namespace std;

typedef struct NODE {
    bool tag;
    struct NODE *Leftchild;
    struct NODE *Rightchild;
}Node;

void Create_and_Check ( int n ) {
    Node *root = (Node *) malloc ( sizeof(Node) );
    root->tag = 0;
    root->Leftchild = NULL;
    root->Rightchild = NULL;

    while ( n-- ) {
        Node *p = root;
        char pre[500000];
        gets ( pre );
        
        for ( int i=0 ; pre[i] ; i++ ) {
            if ( p->tag ) {
                cout << pre << endl;
                exit(0);
            }

            if ( pre[i]-48 ) {
                if ( p->Rightchild ) 
                    p = p->Rightchild;
                else {
                    Node *q = (Node *) malloc ( sizeof(Node) );
                    q->tag = false;
                    q->Leftchild = NULL;
                    q->Rightchild = NULL;
                    p->Rightchild = q;
                    p = q;
                }
            }
            else {
                if ( p->Leftchild ) 
                    p = p->Leftchild;
                else {
                    Node *q = (Node *) malloc ( sizeof(Node) );
                    q->tag = false;
                    q->Leftchild = NULL;
                    q->Rightchild = NULL;
                    p->Leftchild = q;
                    p = q;
                }
            }
        }

        if ( p->Leftchild || p->Rightchild ) {
            cout << pre << endl;
            exit(0);
        }

        p->tag = true;
    }

    cout << "YES" << endl;

    return;
}

int main () {
    int n;
    cin >> n;
    getchar();

    Create_and_Check ( n );

    return 0;
}