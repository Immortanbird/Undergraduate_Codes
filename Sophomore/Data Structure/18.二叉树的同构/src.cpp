/*
* 给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。
* 
* 
* 现给定两棵树，请你判断它们是否是同构的。
* 
* 输入格式：
*   输入给出 2棵二叉树的信息。对于每棵树，第一行中给出一个非负整数N (≤20)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第 i 行对应编号第 i 个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出 “-”。给出的数据间用一个空格分隔。注意：树的根为结点“A"，并保证树中每个结点存储的字母是不同的。
* 
* 输出格式：
*   如果两棵树是同构的，输出“Yes.”，否则输出“No.”。
*/

#include<iostream>
#include<cstdlib>
#include<algorithm>

using namespace std;

typedef struct NODE {
    int data;
    int left;
    int right;
}Node;

bool cmp ( Node x , Node y ) {
    return x.data<y.data;
}

Node *CreateTripple ( int n ) {
    char vec[6];
    Node *tree = (Node *) malloc ( n*sizeof(Node) );

    for ( int i=0 ; i<n ; i++ ) {
        gets ( vec );

        tree[i].data = *vec-64;

        if ( *(vec+2) == '-' ) 
            tree[i].left = -1;
        else 
            tree[i].left = *(vec+2)-48;
        
        if ( *(vec+4) == '-' ) 
            tree[i].right = -1;
        else 
            tree[i].right = *(vec+4)-48;
    }

    for ( int i=0 ; i<n ; i++ ) {
        tree[i].left = tree[tree[i].left].data;
        tree[i].right = tree[tree[i].right].data;
    }

    sort ( tree , tree+n , cmp );

    return tree;
}

void Check ( Node *tree1 , Node *tree2 , int n ) {
    for ( int i=0 ; i<n ; i++ ) {
        bool flag = false;
        if ( tree1[i].left == tree2[i].left && tree1[i].right == tree2[i].right ) 
            flag = true;
        if ( tree1[i].right == tree2[i].left && tree1[i].left == tree2[i].right ) 
            flag = true;
        if ( flag == false ) {
            cout << "No." << endl;
            return;
        }
    }
    cout << "Yes." << endl;

    return;
}

int main () {
    int n;

    cin >> n;
    getchar();
    Node *Tree_a = CreateTripple ( n );
    cin >> n;
    getchar();
    Node *Tree_b = CreateTripple ( n );

    Check ( Tree_a , Tree_b , n );

    return 0;
}