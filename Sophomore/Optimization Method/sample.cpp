#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

const int Max_Component = 100, Max_Machine = 50, MAX_T = 8000;		   //MAX_T表示蒙特卡洛算法初始化次数
const double T = 1000.0, T1 = 0.001, dt = 0.999, L = 50;			   //T表示初始温度，T1表示终止温度，dt表示降温系数，L表示等温迭代次数
int arr[Max_Component][Max_Machine], temp[Max_Component][Max_Machine]; //arr即输入的数组，temp[i][j]表示序列第i个工件完成第j个工序所花时间
int Component, Machine, sum, new_sum;								   //sum表示最优解，new_sum表示当前解
vector<int> sequence;												   //工件的次序
time_t start, finish;

int calc(vector<int> p) //计算序列p调度所花费的时间
{

	temp[0][0] = arr[p[0]][0];
	for (int i = 1; i < Machine; i++)
		temp[0][i] = temp[0][i - 1] + arr[p[0]][i];

	for (int i = 1; i < Component; i++)
		temp[i][0] = temp[i - 1][0] + arr[p[i]][0];

	for (int i = 1; i < Component; i++)
		for (int j = 1; j < Machine; j++)
			temp[i][j] = arr[p[i]][j] + max(temp[i - 1][j], temp[i][j - 1]);

	return temp[Component - 1][Machine - 1];
}

void initialize(int e) //初始化
{
	srand((unsigned)time(NULL));
	sequence.clear();
	start = clock();

	if (e == 0) //仅在第一次执行时读取输入
	{
		scanf("%d%d", &Component, &Machine);
		int m, n;
		for (int i = 0; i < Component; i++)
		{
			for (int j = 0; j < Machine; j++)
			{
				scanf("%d%d", &m, &n);
				arr[i][m] = n;
			}
		}
	}

	for (int i = 0; i < Component; i++)
		sequence.push_back(i);

	sum = calc(sequence), new_sum = 0;
	vector<int> p = sequence;
	for (int t = 0; t < MAX_T; t++) //蒙特卡洛算法初始化
	{
		for (int i = 0; i < Component; i++)
		{
			int j = rand() % Component;
			swap(p[i], p[j]);
		}
		new_sum = calc(p);
		if (sum > new_sum) //如果解比顺序初始化更优，就更新序列与最优值
		{
			sum = new_sum;
			sequence = p;
		}
	}

	return;
}

void simulated_annealing() //模拟退火算法
{
	double t = T;
	while (t >= T1) //t大于等于终止温度时，进行退火过程
	{
		for (int i = 0; i < L; i++) //等温过程
		{
			vector<int> p = sequence;
			int c1 = rand() % Component, c2 = rand() % Component; //用原有序列随机生成新序列
			if (c1 != c2)
			{
				swap(p[c1], p[c2]);
				int dE = calc(p) - sum;				//新调度方案和原有调度方案总耗时之差
				double rd = rand() % 10000 / 10000; //rd为0~1之间的随机数
				if (dE < 0 || exp(-dE / t) > rd)	//如果结果更优就接受，结果不为最优也有一定概率接受
				{
					sum += dE;
					sequence = p;
				}
			}
		}
		t *= dt; //降温过程
	}

	return;
}

void output()
{
	for (int i = 0; i < Component; i++)
		printf("%d,", sequence[i]);

	finish = clock();
	double duration = ((double)(finish - start)) / CLOCKS_PER_SEC;
	printf("\nTimecost: %d\nTime used: %lf\n\n", sum, duration);

	return;
}

int main()
{
	freopen("D:/Personal Files/Codes/C&C++/instance/input10.txt", "r", stdin); //读入数据

	for (int counter = 0; counter < 100; counter++) //对同一组测试用例进行重复测试
	{
		initialize(counter);
		simulated_annealing();
		output();
	}

	return 0;
}