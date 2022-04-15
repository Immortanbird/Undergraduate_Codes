/*
输入：
共两行
第一行 N （ 1<=N<=100 ），代表矩阵个数。
第二行有 N+1 个数，分别为 q(0), q(1), ..., q(n) (1<=q(k)<=2000), 代表第 k 个矩阵是q(k-1)xq(k)维的。

输出：
共两行
第一行 M ，为最优代价。注：测试用例中 M 值保证小于 2^31
第二行为最优顺序。如 (A1((A2A3)A4)) ，最外层也加括号。

注意:测试用例已经保证了输出结果唯一,所以没有AAA的情况.
*/
#include <iostream>

using namespace std;

int s[101];
int trace[101][101];
long step[101][101];

void Traceback(int i, int j)
{
    if (i == j)
        cout << 'A' << i;
    else
    {
        cout << '(';
        Traceback(i, trace[i][j]);
        Traceback(trace[i][j] + 1, j);
        cout << ')';
    }

    return;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n + 1; i++)
        scanf("%d", &s[i]);

    for (int k = 0; k < n; k++) //矩阵链长度
    {
        for (int i = 1; i + k <= n; i++) //矩阵链起点
        {
            if (k == 0)
                step[i][i] = 0;
            else
            {
                step[i][i + k] = step[i][i] + step[i + 1][i + k] + s[i - 1] * s[i] * s[i + k];
                trace[i][i + k] = i;
                for (int t = i + 1; t <= i + k; t++)
                {
                    int temp = step[i][t] + step[t + 1][i + k] + s[i - 1] * s[t] * s[i + k];
                    if (step[i][i + k] > temp)
                    {
                        trace[i][i + k] = t;
                        step[i][i + k] = temp;
                    }
                }
            }
        }
    }

    cout << step[1][n] << endl;
    if (n == 1)
    {
        cout << "(A1)" << endl;
    }
    else
    {
        Traceback(1, n);
        cout << endl;
    }

    return 0;
}