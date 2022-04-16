/* 
* 矩阵的快速转置算法
*   数据压缩是提高传输、存储效率一种技术。教材第5章介绍了两种简单的压缩存储方法。本实验要求实现三元组顺序表表示下的矩阵快速转置算法。
*
* 输入：
*   稀疏矩阵的行数、列数、非零元个数(三个数都大于0)
*   以行为主序输入稀疏矩阵三元组表
* 
* 输出：
*   辅助数组num[ ]
*   辅助数组cpot[ ]
*   以行为主序输出对应的转置矩阵三元组表
*/

#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct Node{
    int x,y,value;
}SparseMatrix;

int cmp ( const void *X , const void *Y ){
    SparseMatrix *M;
    SparseMatrix *N;

    M = (SparseMatrix *) X;
    N = (SparseMatrix *) Y;

    if ( M->x != N->x ) 
        return M->x - N->x;
    else 
        return M->y - N->y;
}

SparseMatrix *CreateMatrix ( int row , int line , int n ) {
    SparseMatrix *M = (SparseMatrix *) malloc ( n*sizeof(SparseMatrix) );
    
    for ( int i=0 ; i<n ; i++ ) 
        cin >> (M+i)->x >> (M+i)->y >> (M+i)->value;
    
    return M;
}

void Output_Num_Cpot ( SparseMatrix *M , int line , int n ){
    cout << "num:";
    int *num = (int *) malloc ( line*sizeof(int) );

    for ( int i=0 ; i<line ; i++ ) 
        *(num+i) = 0;
    
    for ( int i=0 ; i<n ; i++ ) 
        *( num + (M+i)->y - 1) += 1;
    
    for ( int i=0 ; i<line ; i++ ) 
        cout << *(num+i) << ',';
    cout << endl;

    cout << "cpot:";
    int cpot = 1;

    for ( int i=0 ; i<line ; i++ ) {
        cout << cpot << ',';
        cpot += *(num+i);
    }
    cout << endl;

    return;
}


void Transpose ( SparseMatrix *M , int n ) {
    int temp;
    for ( int i=0 ; i<n ; i++ ) {
        temp = (M+i)->x;
        (M+i)->x = (M+i)->y;
        (M+i)->y = temp;
    }

    qsort ( M , n , sizeof(SparseMatrix) , cmp );

    return;
}

void OutputMatrix ( SparseMatrix *M , int n ) {
    for ( int i=0 ; i<n ; i++ ) 
        cout << (M+i)->x << ',' << (M+i)->y << ',' << (M+i)->value << endl;

    return;
}

int main () {
    int row,line,n;
    cin >> row >> line >> n;

    SparseMatrix *M = CreateMatrix ( row , line , n );

    Output_Num_Cpot ( M , line , n );

    Transpose ( M , n );

    OutputMatrix ( M , n );

    return 0;
}