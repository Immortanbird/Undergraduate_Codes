/*
Have you ever played quoit in a playground? Quoit is a game in which flat rings are pitched at some toys, with all the toys encircled awarded. In the field of Cyberground, the position of each toy is fixed, and the ring is carefully designed so it can only encircle one toy at a time. On the other hand, to make the game look more attractive, the ring is designed to have the largest radius. Given a configuration of the field, you are supposed to find the radius of such a ring. Assume that all the toys are points on a plane. A point is encircled by the ring if the distance between the point and the center of the ring is strictly less than the radius of the ring. If two toys are placed at the same point, the radius of the ring is considered to be 0.

Input
The input consists of several test cases. For each case, the first line contains an integer N (2 <= N <= 100,000), the total number of toys in the field. Then N lines follow, each contains a pair of (x, y) which are the coordinates of a toy. The input is terminated by N = 0.

Output
For each test case, print in one line the radius of the ring required by the Cyberground manager, accurate up to 2 decimal places.

Sample Input
2
0 0
1 1
2
1 1
1 1
3
-1.5 0
0 0
0 1.5
0

Sample output
0.71
0.00
0.75
*/
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef struct Node
{
	double x, y;
} Coordinate;

Coordinate location[100005], temp[100005];

bool Compare_X(Coordinate a, Coordinate b)
{
	return a.x < b.x;
}

bool Compare_Y(Coordinate a, Coordinate b)
{
	return a.y < b.y;
}

double Distance(Coordinate u, Coordinate v)
{
	double dx = u.x - v.x;
	double dy = u.y - v.y;
	return sqrt(dx * dx + dy * dy);
}

double MinDistance(int begin, int end)
{
	if (end - begin == 1)
		return Distance(location[begin], location[end]);

	if (end - begin == 2)
	{
		double d1 = Distance(location[begin], location[begin + 1]);
		double d2 = Distance(location[begin], location[end]);
		double d3 = Distance(location[begin + 1], location[end]);
		return min(d1, min(d2, d3));
	}

	int mid_index = (begin + end) / 2;
	double d_left = MinDistance(begin, mid_index);
	double d_right = MinDistance(mid_index + 1, end);
	double d = min(d_left, d_right);

	int n = 0;
	for (int i = 0; i < end - begin + 1; i++)
	{
		if (fabs(location[mid_index].x - location[i].x) <= d)
		{
			temp[n] = location[i];
			n++;
		}
	}
	sort(temp, temp + n, Compare_Y);
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (temp[j].y - temp[i].y >= d)
				break;
			d = min(d, Distance(temp[i], temp[j]));
		}
	}
	return d;
}

int main()
{
	int Num_of_toys;

	while (scanf("%d", &Num_of_toys) && Num_of_toys)
	{
		for (int i = 0; i < Num_of_toys; i++)
			scanf("%lf %lf", &location[i].x, &location[i].y);
		sort(location, location + Num_of_toys, Compare_X);

		printf("%.2f\n", MinDistance(0, Num_of_toys - 1) / 2);
	}

	return 0;
}