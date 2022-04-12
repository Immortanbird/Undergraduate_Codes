#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class CMyString
{
private:
    char *ch;
    int len = 0;
    int size = 0;

public:
    CMyString() = default; /* 默认构造函数 */
    CMyString(int n);
    CMyString(double n);
    CMyString(const char s[]);
    CMyString(const CMyString &str);

    CMyString &operator=(const char s[]);                              /* 重载'=' */
    CMyString operator+(const char s[]);                               /* 重载'+'，连接CMyString对象和const char类型字符串，对象在前 */
    friend CMyString operator+(const char s[], const CMyString str);   /* 重载'+'，连接CMyString对象和const char类型字符串，对象在后 */
    CMyString operator-(const char s);                                 /* 重载'-'，从CMyString对象中移除所有字符s */
    friend ostream &operator<<(ostream &output, const CMyString &str); /* 重载'<<'，从标准输出流输出CMyString对象中的字符串 */
    char &operator[](int index);                                       /* 重载'[]'，从CMyString对象的字符串中取指定位置的字符 */

    int Find(char s);                                  /* 查找CMyString中字符s出现的第一个位置 */
    int Find(const char s[]);                          /* 查找CMyString中字符串s出现的第一个位置，返回首字符出现位置的下标 */
    int Find(int begin, char s);                       /* 从下标为begin开始，向后搜索第一个字符为s的下标 */
    CMyString Mid(int begin, int length_of_substring); /* 从下标为begin的位置开始截取长度为length_of_substring的子串 */

    int ToInt();       /* 字符串逐位转换为整型 */
    double ToDouble(); /* 字符串逐位转换为浮点型 */
};

CMyString::CMyString(int n)
{
    size = 1024;
    ch = (char *)malloc(size * sizeof(char));

    for (len = 0; n > 0; len++)
    {
        ch[len] = n % 10 + '0';
        n /= 10;
    }

    for (int i = 0; i < len / 2; i++)
    {
        int temp = ch[i];
        ch[i] = ch[len - i - 1];
        ch[len - i - 1] = temp;
    }

    ch[len] = '\0';
}

CMyString::CMyString(double n)
{
    double decimal = n - (int)n;
    int integer = n - decimal;

    size = 1024;
    ch = (char *)malloc(size * sizeof(char));

    for (len = 0; integer > 0; len++)
    {
        ch[len] = integer % 10 + '0';
        integer /= 10;
    }

    for (int i = 0; i < len / 2; i++)
    {
        int temp = ch[i];
        ch[i] = ch[len - i - 1];
        ch[len - i - 1] = temp;
    }

    ch[len++] = '.';

    for (; decimal > 0; len++)
    {
        ch[len] = (int)(decimal * 10) + '0';
        decimal = decimal * 10 - (int)(decimal * 10);
    }

    ch[len] = '\0';
}

CMyString::CMyString(const char s[])
{
    ch = (char *)malloc(1024 * sizeof(char));
    int i = 0;
    size = 1024;

    while (s[i] != '\0')
    {
        if (i == size)
        {
            size *= 2;
            ch = (char *)realloc(ch, size * sizeof(char));
        }

        ch[i] = s[i];
        i++;
    }

    len = i;
    ch[len] = '\0';
}

CMyString::CMyString(const CMyString &str)
{
    len = str.len;
    size = str.size;
    ch = (char *)malloc(size * sizeof(char));
    memcpy(ch, str.ch, len);
}

CMyString &CMyString::operator=(const char s[])
{
    if (size)
        free(ch);

    ch = (char *)malloc(1024 * sizeof(char));
    int i = 0;
    size = 1024;

    while (s[i] != '\0')
    {
        if (i == size)
        {
            size *= 2;
            ch = (char *)realloc(ch, size * sizeof(char));
        }

        ch[i] = s[i];
        i++;
    }
    len = i;
    ch[len] = '\0';

    return *this;
}

CMyString CMyString::operator+(const char s[])
{
    int i = len;

    while (s[i] != '\0')
    {
        if (i == size)
        {
            size *= 2;
            ch = (char *)realloc(ch, size * sizeof(char));
        }

        ch[i] = s[i];
        i++;
    }
    len = i;
    ch[len] = '\0';

    return *this;
}

CMyString operator+(const char s[], const CMyString str)
{
    CMyString temp;
    temp.size = 1024;
    temp.ch = (char *)malloc(temp.size * sizeof(char));

    while (s[temp.len] != '\0')
    {
        if (temp.len == temp.size)
        {
            temp.size *= 2;
            temp.ch = (char *)realloc(temp.ch, temp.size * sizeof(char));
        }

        temp.ch[temp.len] = s[temp.len];
        temp.len++;
    }

    for (int i = 0; i < str.len; i++)
    {
        if (temp.len + i == temp.size)
        {
            temp.size *= 2;
            temp.ch = (char *)realloc(temp.ch, temp.size * sizeof(char));
        }
        temp.ch[temp.len + i] = str.ch[i];
    }

    temp.len += str.len;

    temp.ch[temp.len] = '\0';

    return temp;
}

CMyString CMyString::operator-(const char s)
{
    CMyString temp;
    temp.size = size;
    temp.ch = (char *)malloc(size * sizeof(char));

    for (int i = 0; i < len; i++)
    {
        if (ch[i] != s)
        {
            temp.ch[temp.len] = ch[i];
            temp.len++;
        }
    }

    temp.ch[temp.len] = '\0';

    return temp;
}

ostream &operator<<(ostream &output, const CMyString &str)
{
    output << str.ch;

    return output;
}

char &CMyString::operator[](int index)
{
    return ch[index];
}

int CMyString::Find(char s)
{
    for (int i = 0; i < len; i++)
        if (ch[i] == s)
            return i;

    return -1;
}

int CMyString::Find(const char s[])
{
    int i = 0;

    for (; i < len; i++)
    {
        if (s[0] == ch[i])
        {
            for (int j = 1; i + j <= len; j++)
            {
                if (s[j] == '\0')
                    return i;
                if (s[j] != ch[i + j])
                    break;
            }
        }
    }

    return -1;
}

int CMyString::Find(int begin, const char s) /* 从下标为begin开始，搜索第一个s字符的下标 */
{
    while (begin < len)
    {
        if (ch[begin] == s)
            return begin;
        begin++;
    }

    return -1;
}

CMyString CMyString::Mid(int begin, int length_of_substring)
{
    CMyString temp;

    temp.ch = (char *)malloc(length_of_substring * sizeof(char));
    temp.size = length_of_substring;

    for (; temp.len < length_of_substring; temp.len++)
        temp.ch[temp.len] = ch[begin + temp.len];

    temp.ch[len] = '\0';

    return temp;
}

int CMyString::ToInt()
{
    int num = 0;

    for (int i = 0; i < len; i++)
        num += (ch[i] - '0') * pow(10, len - i - 1);

    return num;
}

double CMyString::ToDouble()
{
    double res = 0.0;
    int dot;

    for (int i = 0; i < len; i++)
    {
        if (ch[i] == '.')
        {
            dot = i;
            break;
        }
    }

    for (int i = 0; i < dot; i++)
        res += (ch[i] - '0') * pow(10, dot - i - 1);
    for (int i = dot + 1; i < len; i++)
        res += (ch[i] - '0') * pow(10, dot - i);

    return res;
}
