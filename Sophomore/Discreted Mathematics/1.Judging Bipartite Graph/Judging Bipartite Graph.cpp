#include <iostream>

using namespace std;

int n;
int edge[100][100];
int color[100];

bool dfs(int v, int c)
{
    color[v] = c; //将当前顶点涂色
    for (int i = 0; i < n; i++)
    { //遍历所有相邻顶点，即连着的点
        if (edge[v][i] == 1)
        {                      //如果顶点存在
            if (color[i] == c) //如果颜色重复，就返回false
                return false;
            if (color[i] == 0 && !dfs(i, -c)) //如果还未涂色，就染上相反的颜色-c,并dfs这个顶点，进入下一层
                return false;                 //返回false
        }
    }
    return true; //如果所有顶点涂完色，并且没有出现同色的相邻顶点，就返回true
}

void solve()
{
    for (int i = 0; i < n; i++)
    {
        if (color[i] == 0)
        {
            if (!dfs(i, 1))
            {
                printf("no\n");
                return;
            }
        }
    }
    printf("yes\n");
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> edge[i][j];

    solve();

    return 0;
}