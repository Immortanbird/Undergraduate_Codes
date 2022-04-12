#include <iostream>

using namespace std;

template <typename T>
class CMystack
{
private:
    T stk[10000];
    int stktop;

public:
    CMystack();
    bool empty();
    void push(T x);
    T pop();
    T top();
};

template <class T>
CMystack<T>::CMystack()
{
    stktop = 0;
}

template <class T>
bool CMystack<T>::empty()
{
    if (stktop == 0)
        return 1;
    return 0;
}

template <class T>
void CMystack<T>::push(T x)
{
    stk[stktop++] = x;
    return;
}

template <class T>
T CMystack<T>::pop()
{
    return stk[--stktop];
}

template <class T>
T CMystack<T>::top()
{
    return stk[stktop-1];
}