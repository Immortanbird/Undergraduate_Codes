#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

#define LEN 100000

class MergeSort {
public:
    static void sort(int nums[], int len) {
        int *temp = new int[len];
        sort(nums, 0, len - 1, temp);
    }

private:
    static void sort(int *nums, int left, int right, int *temp) {
        if (left >= right)
            return;

        int mid = (left + right) / 2;
        sort(nums, left, mid, temp);
        sort(nums, mid + 1, right, temp);

        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j<= right) {
            if (nums[i] < nums[j])
                temp[k++] = nums[i++];
            else
                temp[k++] = nums[j++];
        }

        while (i <= mid)
            temp[k++] = nums[i++];

        while (j <= right)
            temp[k++] = nums[j++];

        for (i=left; i <= right; i++)
            nums[i] = temp[i];
    }
};

int nums[LEN];

int main() {
    SYSTEMTIME start, end;

    GetSystemTime(&start);

    freopen("D:\\Codes\\Compiling Principle\\Lab.1.Learning Programing Language\\test.txt", "r", stdin);

    string line;
    int i = 0;
    while (getline(cin, line)) {
        stringstream ss;
        ss << line;

        if (!ss.eof())   
            ss >> nums[i++];
    }

    MergeSort::sort(nums, LEN);
    
    cout << "Sorted(ascending): [" << nums[0];
    for (int i=1; i<LEN; i++)
        cout << ", " << nums[i];
    cout << ']' << endl;
    
    GetSystemTime(&end);
    
    cout << "Timecost: ";
    if (start.wMilliseconds > end.wMilliseconds) 
        cout << end.wSecond - start.wSecond - 1 << 's' << ' ';
    else
        cout << end.wSecond - start.wSecond << 's' << ' ';
    
    cout << abs(end.wMilliseconds - start.wMilliseconds) << "ms" << endl;

    return 0;
}