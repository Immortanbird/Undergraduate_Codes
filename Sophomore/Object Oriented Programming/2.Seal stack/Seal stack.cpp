#include <iostream>
#include <cstdlib>

using namespace std;

class CMystack
{
private:
    double *base;
    double *top;
    int len;

public:
    CMystack(int n);
    int Push(double c);
    int Pop();
    double Gettop();
    void Wipestack();
    bool CheckFull();
    bool CheckEmpty();
};

CMystack::CMystack(int n)//构造函数，构造长度为n+1的数组，下标为零的单元不存储数据
{
    len = n;
    base = top = (double *)malloc((n + 1) * sizeof(double));
    return;
}

int CMystack::Push(double c)//入栈
{
    if (top - base == len)
        return -1;
    else
    {
        top++;
        *top = c;
        return 1;
    }
}

int CMystack::Pop()//出栈
{
    if (top == base)
        return -1;
    else
    {
        top--;
        return 1;
    }
}

double CMystack::Gettop()//取栈顶元素
{
    if (top > base)
        return *top;
}

void CMystack::Wipestack()//清空栈
{
    top = base;
    return;
}

bool CMystack::CheckFull()//判断是否栈满
{
    if (top - base == len)
        return true;
    else
        return false;
}

bool CMystack::CheckEmpty()//判断是否栈空
{
    if (top == base)
        return true;
    else
        return false;
}