#include <iostream>
#include <bitset>

using namespace std;

class IntChar
{
private:
    int ch;

public:
    IntChar(string str);
    void SetNum(int n);
    int INT();
    char At(int n);
    void Print_Binary();
};

IntChar::IntChar(string str)
{
    ch = 0;
    for (int i = 0; i < str.length(); i++)
        ch += str[i] << 8 * (str.length() - i - 1);
}

void IntChar::SetNum(int n)
{
    ch = n;
    return;
}

int IntChar::INT()
{
    return ch;
}

char IntChar::At(int n)
{
    char out = 0;
    out += (ch >> 8 * (4 - n)) & 0b11111111;

    return out;
}

void IntChar::Print_Binary()
{
    bitset<32> bin(ch);
    cout << bin.to_string() << endl;
    
    return;
}