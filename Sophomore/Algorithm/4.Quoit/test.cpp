#include <cstdio>
#include <cmath>
#include <algorithm>
 
using namespace std;
 
#define MAX_N 100005
struct node {
    double x;
    double y;
} point[MAX_N], temp[MAX_N];
 
bool cmp_x(struct node p1, struct node p2) {
    return p1.x < p2.x;
}
 
bool cmp_y(struct node p1, struct node p2) {
    return p1.y < p2.y;
}
 
double CalcDistance(struct node p1, struct node p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

double MinDistance(int start, int end) {
    if (start + 1 == end)  //只有两个点
        return CalcDistance(point[start], point[end]);
    if (start + 2 == end)
    { //只有三个点
        double d1 = CalcDistance(point[start], point[start + 1]);
        double d2 = CalcDistance(point[start + 1], point[end]);
        double d3 = CalcDistance(point[start], point[end]);
        return min(d1, min(d2, d3));
    }
 
    int mid_index = (start + end) / 2;  // x中位数所在点的下标
    double d1 = MinDistance(start, mid_index);  //左边点集内的最小距离
    double d2 = MinDistance(mid_index + 1, end); //右边点集内的最小距离
    double d = min(d1, d2);
 
    int cnt = 0;  //记录temp点集点的个数
    for (int i = start; i <= end; i++)  //把x坐标在中界限[-d，d]附近的点一一收集到temp点集
        if (fabs(point[mid_index].x - point[i].x) <= d)
            temp[cnt++] = point[i];
    sort(temp, temp + cnt, cmp_y); //将temp点集按照y坐标排序
    for (int i = 0; i < cnt; i++)  //直接枚举，找出收集的点集里的最短距离
        for (int j = i + 1; j < cnt; j++) {
            if (temp[j].y - temp[j].y > d)  //没有必要再找了，只会越来越大
                break;
            d = min(d, CalcDistance(temp[i], temp[j]));  //更新最小值
        }
 
    return d;
}
 
int main() {
    int n;
    while (true) {
        /* 处理输入 */
        scanf("%d", &n);
        if (n == 0)
            break;
        for (int i = 0; i < n; i++)
            scanf("%lf %lf", &point[i].x, &point[i].y);
 
        sort(point, point + n, cmp_x);  //先将点按照x坐标排序
        printf("%.2lf\n", MinDistance(0, n - 1) / 2);
    }
}