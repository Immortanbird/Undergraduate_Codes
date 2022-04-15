/*主油管道为东西向，确定主油管道的南北位置，使南北向油井喷油管道和最小。要求线性时间完成。

1<= 油井数量 <=2 000 000

输入要求：

输入有油井数量行，第 K 行为第 K 油井的坐标 X ,Y 。其中， 0<=X<2^31,0<=Y<2^31 。

输出要求：

输出有一行， N 为主管道最优位置的最小值

注意：用排序做的不给分！！*/
#include <iostream>
#include <algorithm>

using namespace std;

long input[2000000];
/*
void InsertionSort(long arr[], int s, int e)
{
    for (int i = s + 1; i < e; i++)
    {
        long key = arr[i];
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            if (key < arr[j])
                arr[j + 1] = arr[j];
            else
            {
                arr[j + 1] = key;
                break;
            }
        }
        if (j < 0)
            arr[i] = key;
    }

    return;
}
*/
void InsertionSort(long arr[], int l, int r)
{
    int j,i;
    for(j = l + 1; j <= r; j++)
    {
        long long tmp = arr[j];
        for(i = j; i > l && arr[i - 1] > tmp; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[i] = tmp;
    }
}

int partition(long arr[], int s, int e, int mid)
{
    int index;
    for (int i = s; i <= e; i++)
    {
        if (arr[i] == mid)
        {
            index = i;
            break;
        }
    }

    swap(arr[index], arr[s]);
    int i = s, j = e + 1;
    while (true)
    {
        while (arr[++i] < mid && i < e)
        {
        }
        while (arr[--j] > mid)
        {
        }
        if (i < j)
            swap(arr[i], arr[j]);
        else
            break;
    }
    swap(arr[s], arr[j]);

    return j;
}

long Select(long arr[], int s, int e, int k)
{
    if (e - s < 75)
    {
        InsertionSort(arr, s, e);
        return arr[s + k - 1];
    }

    for (int i = 0; i <= (e - s - 4) / 5; i++)
    {
        InsertionSort(arr, s + 5 * i, s + 5 * i + 4);
        swap(arr[s + i], arr[s + 5 * i + 2]);
    }

    long mid = Select(arr, s, s + (e - s - 4) / 5, (e - s - 4) / 10);
    int i = partition(arr, s, e, mid);
    int j = i - s + 1;
    if (k <= j)
        return Select(arr, s, i, k);
    else
        return Select(arr, i + 1, e, k - j);
}

int main()
{
    int x;
    int len = 0;

    /*while (len < 11)
    {
        scanf("%d,%d", &x, &input[len]);
        len++;
    }
    */
    while (scanf("%d,%d", &x, &input[len]) != EOF)
        len++;

    int ans = Select(input, 0, len - 1, (len + 1) / 2);

    cout << ans << endl;

    return 0;
}