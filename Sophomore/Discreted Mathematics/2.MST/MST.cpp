#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef struct edge
{
    int v0, v1, value;
    bool choose = 0;
} Edge;

bool cmp(Edge x, Edge y)
{
    return x.value < y.value;
}

void MST_Kruskal(int *V, Edge *E, int v, int e)
{
    int cost = 0;
    V[E[0].v0 - 1] = 1;

    for (int i = 0; i < e; i++)
    {
        if (V[E[i].v0 - 1] + V[E[i].v1 - 1] == 1)
        {
            cost += E[i].value;
            V[E[i].v0 - 1] = 1;
            V[E[i].v1 - 1] = 1;
            E[i].choose = 1;
        }
    }

    for (int i = 0; i < v; i++)
    {
        if (!V[i])
        {
            cout << -1 << endl;
            return;
        }
    }

    for (int i = 0; i < e; i++)
    {
        if (E[i].choose)
            cout << E[i].v0 << ' ' << E[i].v1 << endl;
    }

    cout << cost << endl;

    return;
}

int main()
{
    int v, e;
    cin >> v >> e;

    int *V = (int *)malloc(v * sizeof(int));
    Edge *E = new Edge[e];
    for (int i = 0; i < e; i++)
        cin >> E[i].v0 >> E[i].v1 >> E[i].value;

    sort(E, E + e, cmp);
    memset(V, 0, v * sizeof(int));

    if (!e)
    {
        cout << 0 << ' ' << endl;
        return 0;
    }

    MST_Kruskal(V, E, v, e);

    return 0;
}