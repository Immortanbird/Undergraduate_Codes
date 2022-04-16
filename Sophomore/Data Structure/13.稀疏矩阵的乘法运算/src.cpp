/* 
* 数据压缩是提高传输、存储效率一种技术。教材第5章介绍了两种简单的压缩存储方法。
* 
* 本实验要求实现两个稀疏矩阵相乘积的算法。其中稀疏矩阵非零元素数量小于100.
* 
* 输入：
*   第1个稀疏矩阵
*       行数
*       列数
*       非零元个数(三个数都大于0)
*       三元组
*   第2个稀疏矩阵
*       行数
*       列数
*       非零元个数(三个数都大于0)
*       三元组   
* 注：以行为主序输入稀疏矩阵三元组表
* 
* 输出：
*   乘积矩阵的行数
*   列数
*   非零元个数(三个数都大于0)
*   三元组
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node1{
    int x,y,value;
}Tripple;

typedef struct Node2{
    int row, line, n;
    Tripple *T;
}SparseMatrix;

int Product[3500][3500];

void CreateSparseMatrix ( SparseMatrix *M , int r , int l , int N ) {
    M->row = r;
    M->line = l;
    M->n = N;
    M->T = (Tripple *) malloc ( M->n*sizeof(Tripple) );

    for ( int i=0 ; i<M->n ; i++ ) 
        scanf ( "%d%d%d" , &(M->T+i)->x , &(M->T+i)->y , &(M->T+i)->value );
    
    return;
}

void OutputTripple ( SparseMatrix *M ) {
    printf ( "%d\n%d\n%d\n" , M->row , M->line , M->n );
    for ( int i=0 ; i<M->n ; i++ ) 
        printf ( "%d,%d,%d\n" , (M->T+i)->x , (M->T+i)->y , (M->T+i)->value );
    
    return;
}

int Calculate ( SparseMatrix *M1 , SparseMatrix *M2 ) {
    memset ( Product , 0 , sizeof(Product) );

    for ( int i=0 ; i<M1->n ; i++ ) {
        for ( int j=0 ; j<M2->n ; j++ ) {
            if ( (M2->T+j)->x == (M1->T+i)->y ) 
                Product[(M1->T+i)->x][(M2->T+j)->y] += (M1->T+i)->value * (M2->T+j)->value;
        }
    }

    int sum = 0;

    for ( int i=1 ; i<100 ; i++ ) {
        for ( int j=1 ; j<100 ; j++ ) {
            if ( Product[i][j] )
                sum++;
        }
    }

    return sum;
}

void GetResult ( SparseMatrix *Q ) {
    int n = 0;
    for ( int i=1 ; i<100 ; i++ ) {
        for ( int j=1 ; j<100 ; j++ ) {
            if ( Product[i][j] ) {
                (Q->T+n)->x = i;
                (Q->T+n)->y = j;
                (Q->T+n)->value = Product[i][j];
                n++;
            }
        }
    }
    
    return;
}

int main () {
    int row, line, n;
    SparseMatrix M1,M2,Q;

    scanf ( "%d%d%d" , &row , &line , &n );
    CreateSparseMatrix ( &M1 , row , line , n );

    scanf ( "%d%d%d" , &row , &line , &n );
    CreateSparseMatrix ( &M2 , row , line , n );

    Q.row = M1.row;
    Q.line = M2.line;
    Q.n = Calculate ( &M1 , &M2 );    
    Q.T = (Tripple *) malloc ( Q.n*sizeof(Tripple) );
    GetResult ( &Q );
    OutputTripple ( &Q );

    return 0;
}