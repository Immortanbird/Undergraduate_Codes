#include <iostream>

using namespace std;

int matrix[100][100];

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matrix[i][j];

    if (n == 5)
    {
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int j = 0; j < n; j++)
                sum += matrix[i][j];
            cout << sum << ' ';
            sum = 0;
            for (int j = 0; j < n; j++)
                sum += matrix[j][i];
            cout << sum;

            if (i < n - 1)
                cout << ' ' << endl;
            else
                cout << endl;
        }

        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += matrix[i][j];
        cout << sum << ' ';
        sum = 0;
        for (int j = 0; j < n; j++)
            sum += matrix[j][i];
        cout << sum << endl;
    }

    return 0;
}