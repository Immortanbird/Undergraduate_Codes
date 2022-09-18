# 程序设计语言认知实验报告

* ## 实验目的

​	了解程序设计语言的发展历史，了解不同程序设计语言的各自特点；感受编译执行和解释执行两种不同的执行方式，初步体验语言对编译器设计的影响，为后续编译程序的设计和开发奠定良好的基础。

* ## 实验内容

​	分别使用C/C++、Java 、Python和Haskell 实现归并排序，对采用这几种语言实现的编程效率、程序的规模、程序的运行效率进行对比分析。

* ## 实验过程

  * C++
```C++
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
```
  * Java
```Java
import java.io.IOException;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;

public class MergeSort {
    final static int LEN = 100000;

    public static void main(String[] args) throws IOException {
        long start = System.currentTimeMillis();

        int[] nums = new int[LEN];

        Scanner scanner = new Scanner(Paths.get("D:\\Codes\\Compiling Principle\\Lab.1.Learning Programing Language\\test.txt"), "UTF-8");

        for (int i=0; i<nums.length && scanner.hasNextInt(); i++)
            nums[i] = scanner.nextInt();

        sort(nums);

        System.out.println("Sorted(ascending):");
        System.out.println(Arrays.toString(nums));

        long end = System.currentTimeMillis();

        System.out.println("Timecost: " + (end - start) + "ms");
    }

    public static void sort(int[] nums) {
        int[] temp = new int[nums.length];
        sort(nums, 0, nums.length - 1, temp);
    }

    private static void sort(int[] nums, int left, int right, int[] temp) {
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
}
```
  * Python
```Python
import time


def merge(arr, l, m, r):
    n1 = m - l + 1
    n2 = r - m

    L = [0] * n1
    R = [0] * n2

    for i in range(0, n1):
        L[i] = arr[l + i]

    for j in range(0, n2):
        R[j] = arr[m + 1 + j]

    i = 0
    j = 0
    k = l

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        arr[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = R[j]
        j += 1
        k += 1


def mergesort(arr, l, r):
    if l < r:
        m = int((l + (r - 1)) / 2)

        mergesort(arr, l, m)
        mergesort(arr, m + 1, r)
        merge(arr, l, m, r)


start = time.time()

arr = []

with open("D:/Codes/Compiling Principle/Lab.1.Learning Programing Language/test.txt", 'r') as file:
    for line in file:
        arr.append(int(line.rstrip()))

n = len(arr)

mergesort(arr, 0, n - 1)

print("Sorted(ascending): ", arr, '\n')

end = time.time()

print("Timecost: ", int(round((end - start) * 1000)), "ms\n")

```
  * Haskell

    由于Haskell的文件输入较为复杂，实际测试过程中直接将测试用例的数据填入了源码的列表中。

```Haskell
module Main where
import Control.Monad.Writer


merge [] xs = xs
merge xs [] = xs
merge (x:xs) (y:ys)
  | x<=y = x:merge xs (y:ys)
  | otherwise = y:merge (x:xs) ys


mergesort :: Int -> [Int] -> Writer String [Int]
mergesort l [] = do
  return []


mergesort l s@[x] = do
  return [x]


mergesort l s@xs = do
  let (a1,a2) = splitAt (length s `div` 2) xs
  curMergeResult <- liftM2 merge (mergesort (l+2) a1) (mergesort (l+2) a2)
  return curMergeResult
  

main :: IO ()
main = do
  let res = runWriter $ mergesort 0 [5,4,3,10,9,101,2,1]
  
  putStrLn $show $ fst $res
```

* ## 运行效果截图
  * C++

  ![Panel](image\C++.png)
  
  * Java

  ![Panel](image\Java.png)

  * Python
  
  ![Panel](image\Python.png)
  
  * Haskell

  ![Panel](image\Haskell.png)
  
* ## 语言易用性和程序规模对比分析

​	从本次实验来看，Java和C++的语言易用性略高于Python和Haskell。
​	Java和C++作为静态强类型语言，使用时变量的类型和定义更加明确，语法也更加清晰明了。而Python在声明变量时不需要指明变量的类型，并且变量类型可以在运行时改变，容易导致混淆。Haskell作为函数式编程语言，编程思想比较复杂难懂，学习成本比较高。
​	从代码规模的角度来看，Java、C++和Python的代码规模相差不大，而Haskell代码规模明显小于前三者。

* ## 程序运行性能对比分析

  * CPU: Intel i5-10210U, 4核
  * L1: 256KB
  * L2: 1.0MB
  * L3: 6.0MB
  * 内存: 15.6GB

|          | C++       | Java     | Python     | Haskell   |
| -------- | --------- | -------- | ---------- | --------- |
| 平均用时 | 12s 946ms | 0s 423ms | 0s 710.8ms | 10s 692ms |

​	以上数据采用了长度为10万的逆序正整数数组，运行5次取均值获得。
​	显然，Java和Python的运行速度远高于C++和Haskell。
​	然而，如果不计入输出结果数组所消耗的时间，C++与Java耗时相近；Python耗时略高于前两者；而对于Haskell，由于计时是在ghci命令行中使用`:set +s`实现的，精度仅精确到0.01秒，所以无法确定，但可以肯定也和C++与Java耗时相近，甚至可能更快。

* ## 实验心得体会

​	编程语言的易用性在很大程度上会影响语言的使用范围。C++、Java和Python简洁明了的语法和编程风格使其更容易学习和使用。而相比之下，Haskell语言就比较晦涩难懂，其编程逻辑也比较复杂，需要花费大量时间去深入理解，才能够熟练掌握其编程思想。
​	关于不同语言的运行效率，普遍认为编译型语言的效率高于解释型语言。然而在实验中，C++和Java在不考虑输出用时的情况下，两者耗时相近。因此，个人认为评价语言的运行效率应当考虑到特定的使用环境。
​	关于C++和Haskell输出耗时长的问题，个人认为可能是在Windows控制台中运行的缘故。关于输出耗时的问题有待进一步研究。