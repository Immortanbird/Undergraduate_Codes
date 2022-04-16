/* 
* 设顺序存储的二叉树中有编号为 i 和 j 的两个结点，请设计算法求出它们最近的公共祖先结点的编号和值。
* 
* 输入：
*   输入第1行给出正整数n（≤1000），即顺序存储的最大容量；
*   第2行给出n个非负整数，其间以空格分隔。其中0代表二叉树中的空结点（如果第1个结点为0，则代表一棵空树）；
*   第3行给出一对结点编号i和j。
* 
* 题目保证输入正确对应一棵二叉树，且1≤i,j≤n。
* 
* 输出：
*   如果i或j对应的是空结点，则输出：ERROR: T[x] is NULL，其中x是i或j中先发现错误的那个编号；否则在一行中输出编号为i和j的两个结点最近的公共祖先结点的编号和值，其间以一个空格分隔。
*/

#include<iostream>
#include<queue>

using namespace std;

void CheckInput ( int *in , int sib1 , int sib2 ) {
    if ( in[sib1-1] == 0 ) {
        printf ( "ERROR: T[%d] is NULL\n" , sib1 );
        exit(0);
    }

    if ( in[sib2-1] == 0 ) {
        printf ( "ERROR: T[%d] is NULL\n" , sib2 );
        exit(0);
    }

    return;
}

int Search_for_Father ( int *in , int sib1 , int sib2 ) {
    sib1 -= 1;
    sib2 -= 1;
    while ( sib1 != sib2 ) {
        if ( sib1 > sib2 ) 
            sib1 = (sib1+1)/2-1;
        if ( sib2 > sib1 ) 
            sib2 = (sib2+1)/2-1;
    }

    return sib1;
}

int main () {
    int n;
    cin >> n;

    int *input = (int *) malloc ( n*sizeof(int) );
    
    for ( int i=0 ; i<n ; i++ ) 
        cin >> input[i];

    int sib1,sib2;
    cin >> sib1 >> sib2;

    CheckInput ( input , sib1 , sib2 );

    int preCommmonAncestor = Search_for_Father ( input , sib1 , sib2 );

    cout << preCommmonAncestor+1 << ' ' << input[preCommmonAncestor] << endl;

    return 0;
}