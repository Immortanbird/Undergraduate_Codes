/* Description
Jimmy works in an express company. His job is to deliver the packages to customers as soon as possible. He should deliver all the packages to their customers according to the orders before the end of the day, i.e. 24:00. Any delay should be fined heavily measured by the time he is late for.
It was a bad day. Jimmy' car was broken. And when he repaired it. It was exactly 24:00. The only thing Jimmy thought then was to find a proper way to deliver to minimize the fine.
He took a look at the map and found that his current position and all the places he would go are on a circle road. And he can drive his car to any place along the circle road clockwise or counter-clockwise. He wanted you to help him to find the best way to minimize the fine.
The fine is described as follows: if Jimmy is late, he has to pay one dollar per minute for each undelivered package.

Input
The input contains several test cases. The first line in each case contains an integer N, no more than 300, where (N-1) is the number of places he has to deliver to. The following N lines describe N points including his current location and the (N-1) destinations he has to go to. These N points are described clockwise based on their locations from Jimmy's current location. Each line consists of two integers m and t. m is the number of packages ordered by this place, which is always 0 in the first line and positive integers in the other lines. t, measured in minute, represents the time to go from this point to the next (the next point of the (N-1)-th destinations is Jimmy's current location).
A test case with N = 0 indicates the end of input, and this case should not be processed.

Output
For each test case, you should output one line containing only an integer which is the minimum fine Jimmy has to pay. You can assume that the answer is less than 1000000000 for all test cases.

Sample Input
4
0 1
6 10
9 50
5 5
5
0 2
5 5
4 20
1 20
7 1
0

Sample Output
240
92
*/
#include <iostream>

using namespace std;

int time_clockwise[305];
int time_counter_clockwise[305];


int main()
{
    int dest;

    while (scanf("%d", &dest) && dest)
    {
        int *package = new int[dest];
        int *time = new int[dest];

        for (int i = 0; i < dest; i++)
            cin >> package[i] >> time[i];


    }

    return 0;
}