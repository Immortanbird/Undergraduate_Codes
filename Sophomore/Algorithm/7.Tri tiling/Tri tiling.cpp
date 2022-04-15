/*
Description
In how many ways can you tile a 3xn rectangle with 2x1 dominoes? Find the answer taken modulo 9973.

Input
Input consists of several test cases followed by a line containing -1. Each test case is a line containing an integer 0 <= n <= 109.

Output
For each test case, output one non negative integer, which is the number of possible tilings modulo 9973.

Sample Input
2
8
12
-1

Sample Output
3
153
2131
*/
#include <iostream>

using namespace std;

int dp[100000];

int main()
{
    dp[2] = 3;
    dp[4] = 11;
    for (int i = 6; i < 100000; i += 2)
    {
        dp[i] = (4 * dp[i - 2] - dp[i - 4]) % 9973;
        if (dp[i] <= 0)
            dp[i] += 9973;
    }

    long long n;
    while (scanf("%lld", &n) && n != -1)
    {
        n %= 19944;
        if (n == 0) {
            cout << 1 << endl;
            continue;
        }

        if (n % 2)
            printf("0\n");
        else
            printf("%d\n", dp[n]);
    }

    return 0;
}