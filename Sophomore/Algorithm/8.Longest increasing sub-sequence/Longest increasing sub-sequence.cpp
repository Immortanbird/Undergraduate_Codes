/*
Given a sequence x(1),...,x(n) of integers (not necessarily positive). A sub-sequence satisfies x(i1)≤x(i2)≤…≤x(ik) (i1<i2<…<ik) is called a increasing sub-sequence with length k. 

Input：
Two rows
The first row is an integer n (1<=n<=10000), indicating the number of integers in the sequence.
The second row has n integers, x(1),...,x(n) (|x(k)|<2000).

Output：
The length of longest increasing sub-sequence.

Sample input
10
2,8,9,4,6,1,3,7,5,10

Sample output
5
*/
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int *seq = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d,", &seq[i]);

    int *len = new int[n];
    for (int i = 0; i < n; i++)
        len[i] = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (seq[i] >= seq[j] && len[j] + 1 > len[i])
                len[i] = len[j] + 1;
        }
    }
    
    sort(len, len + n);

    cout << len[n - 1] << endl;

    return 0;
}