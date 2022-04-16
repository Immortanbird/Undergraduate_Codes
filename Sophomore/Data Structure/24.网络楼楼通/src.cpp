/* 
* 现有学校宿舍区之间要铺设光纤建设网络，在施工预算的统计数据表中，列出了有可能建设光缆的若干条管线的成本，求使每栋楼都能够接入校园网且使管网建设费用成本最低。
* 
* 输入：
*   第一行数据包括楼宇的数目正整数N（≤1000）和候选管网数目M（≤3N）；
*   随后的M行对应M条线路，每行给出3个正整数，分别是该条线路直接连通的两个楼宇的编号以及预算成本（为简单起见，城镇从1到N编号）。
* 
* 输出：
*   输出建设楼楼通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多的通路。
*/

#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>

using namespace std;

typedef struct NODE {
    int begin,end,value;
}Arc;

bool cmp ( Arc a , Arc b ){
    return a.value < b.value;
}

Arc *Input ( int Num_A ) {
    Arc *list = (Arc *) malloc ( Num_A*sizeof(Arc) );

    for ( int i=0 ; i<Num_A ; i++ ) 
        cin >> (list+i)->begin >> (list+i)->end >> (list+i)->value;

    return list;
}

int Check_loop ( int *MST , int x ) {
    if ( MST[x] == x ) 
        return x;
    else 
        return MST[x] = Check_loop( MST , MST[x] );
}

int GenerateMST ( Arc *list , int Num_n , int Num_a ) {
    int sum = 0;
    int arcs = 0;
    int *MST = (int *) malloc ( (Num_n+1)*sizeof(int) );
    for ( int i=0 ; i<Num_n+1 ; i++ ) 
        *(MST+i) = i;

    for ( int i=0 ; i<Num_a && arcs<Num_n-1 ; i++ ) {
        int p = Check_loop ( MST , list[i].begin );
        int q = Check_loop ( MST , list[i].end );
        if ( p != q ) {
            MST[p] = q;
            sum += list[i].value;
            arcs++;
        }
    }

    if ( arcs == Num_n-1 ) 
        return sum;

    return -1;
}

int main () {
    int Num_Nodes,Num_Arcs;

    cin >> Num_Nodes >> Num_Arcs;

    Arc *AdjacencyList = Input ( Num_Arcs );

    sort ( AdjacencyList , AdjacencyList+Num_Arcs , cmp);

    cout << GenerateMST ( AdjacencyList , Num_Nodes , Num_Arcs ) << endl;

    return 0;
}