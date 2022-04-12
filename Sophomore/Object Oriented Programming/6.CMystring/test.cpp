#include "CInternetURL.h"

using namespace std;

int main()
{
    CInternetURL URL("https://www.bit.edu.cn/xww/lgxb21/067aaa91b7524e7f9a43a5263633fcf4.htm");
    cout << URL.GetDomainCountry() << endl << URL.GetDomainType() << endl;
    
    return 0;
}