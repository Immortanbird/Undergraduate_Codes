#include "CExpression.h"

using namespace std;

int main()
{
    CExpression expr;
    expr.SetExpression("(12+4)/4");
    printf("%lf\n", expr.Value());

    return 0;
}