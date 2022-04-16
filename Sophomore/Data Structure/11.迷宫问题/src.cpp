/* 
* 迷宫有一个入口，一个出口。一个人从入口走进迷宫，目标是找到出口。阴影部分和迷宫的外框为墙，每一步走一格，每格有四个可走的方向，探索顺序为地图方向：南（下）、东（右）、北（上）、西（左）。

* 输入：输入迷宫数组。第一行数据表示一个 n*n (n<=100)的迷宫；第二行开始的n行为迷宫数据。
* 其中：0表示路，1表示墙，起点在左上角 <1,1> 的位置，终点在右下角 <n,n> 的位置。
* 输出：若有解，输出从入口到出口的一条路径，否则输出 there is no solution!
* 
* 例（上图所示的迷宫数组）
* 输入：
*   4 4
*   0 0 1 0
*   0 1 0 1
*   0 0 0 0
*   0 1 0 0 
* 输出：<1,1> <2,1> <3,1> <3,2> <3,3> <4,3> <4,4>
*/

#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct NODE{
    int x;
    int y;
    struct NODE *next;
}Coordinate;

const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};
int map[102][102],visited[102][102];
Coordinate *stk = NULL;
int r,l;

void InitiateMap ( int r , int l ) {
    for ( int i=0 ; i<r+2 ; i++ ) {
        for ( int j=0 ; j<l+2 ; j++) {
            map[i][j] = 1;
            visited[i][j] = 0;
        }
    }

    for ( int i=1 ; i<r+1 ; i++ ) {
        for ( int j=1 ; j<l+1 ; j++) {
            map[i][j] = 0;
        }
    }

    return;
}

void InputMap ( int r , int l ) {
    for ( int i=1 ; i<=r ; i++ ) {
        for ( int j=1 ; j<=l ; j++) {
            cin >> map[i][j];
        }
    }

    return;
}

void Push ( int x , int y ) {
    Coordinate *p = (Coordinate *) malloc ( sizeof(Coordinate) );
    p->next = stk;
    p->x = x;
    p->y = y;
    stk = p;

    visited[x][y] = 1;

    return;
}

void Pop() {
    Coordinate *temp;
    temp = stk;
    stk = stk->next;
    free ( temp );

    return;
}

void Output() {
    Coordinate *Head = stk;
	Coordinate *p,*q;
    p = NULL;

	while ( Head ) {
		q = Head;
        Head = Head->next;

        q->next = p;
        p = q;
	}

    while ( p ) {
        printf ( "<%d,%d> " , p->x , p->y );
        p = p->next;
    }
    cout << endl;

    return;
}

void DFS () {
    while ( stk ) {
        bool flag = true;
        int i,x,y;

        for ( i=0 ; i<4 ; i++ ) {
            x = stk->x + dx[i];
            y = stk->y + dy[i];

            if ( map[x][y] == 0 && visited[x][y] == 0 ) {
                if ( x == r && y == l ) {
                    Push ( x , y );
                    Output();
                    return;
                }

                Push ( x , y );
                break;
            }
                
            if ( i == 3 ) 
                flag = false;
        }
        
        if ( !flag ) {
            map[stk->x][stk->y] = 1;
            Pop();
        }
    }

    cout << "There is no solution!" << endl;

    return;
}

int main () {

    cin >> r >> l;

    InitiateMap ( r , l );

    InputMap ( r , l );

    Push ( 1 , 1 );

    DFS();

    return 0;
}