/* 
* 用堆排序算法按关键字递减的顺序排序。
* 
* 输入：待排序记录数（整数）和待排序记录（整数序列）
* 
* 输出：建堆结果和建堆后第一、第二次筛选结果。（注：待排序记录数大于等于3）
*/

#include<iostream>
#include<cstdlib>

using namespace std;

void HeapAdjust ( int heap[] , int s , int n ) {
    int P = s;
    int C = 2*P+1;

    while ( C < n ) {
        if ( C+1 < n ) {
            if ( heap[P] > heap[C] && heap[P] > heap[C+1] ) 
                return;
            else {
                if ( heap[C] > heap[C+1] ) {
                    int temp = heap[C];
                    heap[C] = heap[P];
                    heap[P] = temp;
                    P = C;
                    C = 2*P+1;
                }
                else {
                    int temp = heap[C+1];
                    heap[C+1] = heap[P];
                    heap[P] = temp;
                    P = C+1;
                    C = 2*P+1;
                }
            }
        }
        else {
            if ( heap[P] > heap[C] ) 
                return;
            else {
                int temp = heap[C];
                heap[C] = heap[P];
                heap[P] = temp;
                return;
            }
        }
        
    }
    
    return;
}

void HeapSort ( int heap[] , int len ) {
    for ( int i=(len-1)/2 ; i>=0 ; i-- ) {
        HeapAdjust ( heap , i , len );
    }

    return;
}

void PrintHeap ( int *heap , int n ) {
    for ( int i=0 ; i<n ; i++ ) 
        cout << heap[i] << ' ';
    cout << endl;

    return;
}

int main () {
    int len,temp;
    cin >> len;

    int *Heap = (int *) malloc ( len*sizeof(int) );

    for ( int i=0 ; i<len ; i++ ) 
        cin >> Heap[i];

    HeapSort ( Heap , len );
    PrintHeap ( Heap , len );

    temp = Heap[0];
    Heap[0] = Heap [len-1];
    Heap[len-1] = temp;
    HeapSort ( Heap , len-1 );
    PrintHeap ( Heap , len -1 );

    temp = Heap[0];
    Heap[0] = Heap [len-2];
    Heap[len-2] = temp;
    HeapSort ( Heap , len-2 );
    PrintHeap ( Heap , len-2 );

    return 0;
}