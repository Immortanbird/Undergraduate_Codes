/* 
* 程序的输入是一个表示树结构的广义表。假设树的根为 root ，其子树森林 F ＝ （ T1 ， T2 ， … ， Tn ），设与该树对应的广义表为 L ，则 L ＝（原子，子表 1 ，子表 2 ， … ，子表 n ），其中原子对应 root ，子表 i （ 1<i<=n ）对应 Ti 。例如：广义表 (a,(b,(c),(d)),(f,(g),(h ),(i))) 表示的树如图所示：

* 程序的输出为树的层次结构、树的度以及各种度的结点个数。

* 在输出树的层次结构时，先输出根结点，然后依次输出各个子树，每个子树向里缩进 4 个空格，如：针对上图表示的树，输出的内容应为：
* a
*     b
*         c
*         d
*     f
*         g
*         h
*         i
* Degree of tree: 3
* Number of nodes of degree 0: 5
* Number of nodes of degree 1: 0
* Number of nodes of degree 2: 2
* Number of nodes of degree 3: 1
* 
* 例：（下面的黑体为输入）
* (a,(b),(c,(d),(e,(g),(h )),(f)))
* a
*     b
*     c
*         d
*         e
*             g
*             h
*         f
* Degree of tree: 3
* Number of nodes of degree 0: 5
* Number of nodes of degree 1: 0
* Number of nodes of degree 2: 2
* Number of nodes of degree 3: 1
*/

#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

void PrintTree ( char *seq ) {
    int depth = -1;

    while ( *seq ) {
        if ( *seq == '(' ) 
            depth++;

        if ( *seq == ')' ) 
            depth--;

        if ( *seq >= 'a' && *seq <= 'z' ) {
            for ( int i=0 ; i<4*depth ; i++ ) 
                cout << ' ';
            cout << *seq << endl;
        }
        seq++;
    }

    return;
}

void CalculateDegree ( char *seq ) {
    int Point = 0;
    int deg, degs[100] = { 0 };
    while (seq[Point] != '\0') {
        if (seq[Point] == '(') {
            int L_Num = 1;
            int Ds = 0;
            int Flag = 0;
            seq[Point] = ' ';
            for (int i = Point + 1; seq[i] != '\0'; i++) {
                if (seq[i] >= 'a' && seq[i] <= 'z') 
                    Flag = 1;
                if (seq[i] == '(')
                    L_Num++;
                if (seq[i] == ')') {
                    L_Num--;
                    if (L_Num == 0) {    
                        seq[i] = ' ';    
                        break;    
                    }    
                }    
                if (seq[i] == ',' && L_Num == 1) {    
                    Ds++;    
                    seq[i] == ' ';    
                }    
            }    
            if (Flag)    
                degs[Ds]++;    
        }    
        Point++;    
    }
    for(int i = 99; i >= 0; i--) {
        if (degs[i] != 0) {    
            deg = i;
            break;
        }
    }

    cout << "Degree of tree: " << deg << endl;
    for ( int i=0 ; i<=deg ; i++ )  
        cout << "Number of nodes of degree " << i << ": " << degs[i] << endl;

    return;
}

int main () {
    char sequence[10000];
    gets ( sequence );

    PrintTree ( sequence );

    CalculateDegree ( sequence );

    return 0;
}