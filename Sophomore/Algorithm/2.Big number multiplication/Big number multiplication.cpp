/*
问题描述

计算最多20010位十进制正整数A和B的乘积A*B。

输入样例
1259
8

输出样例
10072
*/
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char A[20015], B[20015];
    int len1, len2;
    gets(A);
    gets(B);

    len1 = strlen(A);
    len2 = strlen(B);

    int Num1[20010], Num2[20010], result[40025];
    for (int i = 0; i < len1; i++)
        Num1[len1 - 1 - i] = A[i] - '0';
    for (int i = 0; i < len2; i++)
        Num2[len2 - 1 - i] = B[i] - '0';

    memset(result, 0, sizeof(result));

    for (int j = 0; j < len2; j++)
        for (int i = 0; i < len1; i++)
            result[i + j] += Num1[i] * Num2[j];

    for (int i = 0; i < len1 + len2; i++)
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int len = len1 + len2;
    while (!result[len])
        len--;
    while (len >= 0)
    {
        cout << result[len];
        len--;
    }
    cout << endl;

    return 0;
}