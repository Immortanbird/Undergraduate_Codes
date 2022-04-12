#include <iostream>
#include <cmath>
#include "CMystack.h"

using namespace std;

class CExpression
{
private:
    CMystack<double> OPND;
    CMystack<char> OPTR;
    char priority[7][7] = {
        //运算符优先级表
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'<', '<', '<', '<', '<', '=', '0'}, // 此行"="表示左右括号相遇，括号内运算已完成
        {'>', '>', '>', '>', '0', '>', '>'},
        {'<', '<', '<', '<', '<', '0', '='} // "=" 表示整个表达式求值完毕
    };
    string expression; //初始表达式
    int GetOperand(int i);
    char Proceed(char a, char b);               //建立priority[][]到对应运算符间的映射关系
    double Operate(double m, double n, char x); //数值计算

public:
    void SetExpression(string s);
    double Value();
};

int CExpression::GetOperand(int i)
{
    double num = 0.00;
    int begin = i, end, point = 0;                                                 //begin:数字的开头;end:数字的末尾下标;point:如果是小数，小数点的下标
    while ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') //确认是否是小数
    {
        if (expression[i] == '.')
            point = i;
        i++;
    }
    end = i - 1;
    if (point)
    {
        for (int m = 0; m < point - begin; m++)
            num += (expression[begin + m] - '0') * pow(10, point - begin - m - 1);
        for (int m = 0; m <= end - point; m++)
            num += (expression[begin + m] - '0') * pow(10, -m);
    }
    else
    {
        for (int m = 0; m <= end - begin; m++)
            num += (expression[begin + m] - '0') * pow(10, end - begin - m);
    }
    OPND.push(num); //将操作数入栈
    return end;
}

char CExpression::Proceed(char a, char b)
{
    int i, j;
    switch (a)
    {
    case '+':
        i = 0;
        break;
    case '-':
        i = 1;
        break;
    case '*':
        i = 2;
        break;
    case '/':
        i = 3;
        break;
    case '(':
        i = 4;
        break;
    case ')':
        i = 5;
        break;
    case '#':
        i = 6;
        break; // # 是表达式的结束符
    }
    switch (b)
    {
    case '+':
        j = 0;
        break;
    case '-':
        j = 1;
        break;
    case '*':
        j = 2;
        break;
    case '/':
        j = 3;
        break;
    case '(':
        j = 4;
        break;
    case ')':
        j = 5;
        break;
    case '#':
        j = 6;
        break;
    }
    return priority[i][j];
}

double CExpression::Operate(double m, double n, char x)
{
    switch (x)
    {
    case '+':
        return m + n;
    case '-':
        return n - m;
    case '*':
        return m * n;
    case '/':
        return n / m;
    }
}

void CExpression::SetExpression(string s)
{
    expression = s;
    return;
}

double CExpression::Value()
{
    OPTR.push('#');
    for (int i = 0; i < expression.size() || OPTR.top() != '#'; i++)
    {
        char c = 0;
        if (i < expression.size())
            c = expression[i];
        if ((c >= '0' && c <= '9') || c == '.')
            i = GetOperand(i);
        else
        {
            switch (Proceed(OPTR.top(), c))
            {
            case '<': //栈顶元素优先级低，将运算符入栈
                OPTR.push(c);
                break;
            case '=':
                OPTR.pop(); //左右括号匹配
                break;
            case '>': //栈顶元素优先级高，退栈并计算
                char x = OPTR.top();
                OPTR.pop();
                if (OPTR.top() == '(')
                    OPTR.pop();
                double m = OPND.top();
                OPND.pop();
                double n = (OPND.top)();
                OPND.pop();
                OPND.push(Operate(m, n, x));
                break;
            }
        }
    }
    return OPND.top();
}