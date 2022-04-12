#include "IntChar.h"

using namespace std;

int main()
{
    IntChar IC ("ABCD");
    cout << IC.INT() << endl;
    IC.Print_Binary();
    IC.SetNum(100);
    cout << IC.INT() << endl;
    IC.Print_Binary();

    return 0;
}