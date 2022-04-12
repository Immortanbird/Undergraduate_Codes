#include <iostream>
#include <cstring>

using namespace std;

class LINT
{
private:
    int mem[27];
    int len;

public:
    LINT(const char str[]);
    LINT Add(const LINT &L1, const LINT &L2, const LINT &L);
    void Print();
};

LINT::LINT(const char str[])
{
    memset(mem, 0, sizeof(mem));
    len = strlen(str);
    for (int i = 0; i < (len + 3) / 4; i++)
    {
        int j = i * 4;
        for (int k = 0; j + k < len && k < 4; k++)
            mem[i] += str[j + k] << 8 * (3 - k);
    }
}

LINT LINT::Add(const LINT &L1, const LINT &L2, const LINT &L)
{
}

void LINT::Print()
{

    return;
}