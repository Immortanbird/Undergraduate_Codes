#include <iostream>
using namespace std;
int main()
{
    int p[50][50];
    int a[50][50];
    int i, j, k, m, n;

    cin >> n;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            cin >> a[i][j];

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            p[i][j] = a[i][j];

    //Warshall 算法
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (p[j][i] == 1)
            {
                for (k = 0; k < n; k++)
                {
                    p[j][k] = p[j][k] + p[i][k];
                    if (p[j][k] != 0)
                    {
                        p[j][k] = 1;
                    }
                }
            }
        }
    }

    int cnt = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (p[i][j] == 1)
            {
                cnt++;
            }
        }
    }
    if (cnt == n * n)
    {
        cout << 'A' << endl;
        return 0;
    }
    cnt = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                break;
            }
            if (p[i][j] + p[j][i] > 0)
            {
                cnt++;
            }
        }
    }
    if (2 * cnt == (n * n - n))
    {
        cout << 'B' << endl;
        return 0;
    }
    //改造矩阵
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (a[i][j] == 1 || a[j][i] == 1)
            {
                a[i][j] = 1;
                a[j][i] = 1;
            }
        }
    }

    cnt = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                break;
            }
            if (a[i][j] == 1)
            {
                cnt++;
            }
        }
    }
    if (2 * cnt == (n * n - n))
    {
        cout << 'C' << endl;
    }
    return 0;
}