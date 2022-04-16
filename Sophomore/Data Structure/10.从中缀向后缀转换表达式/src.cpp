/*
* 问题描述
*   中缀表达式就是我们通常所书写的数学表达式，后缀表达式也称为逆波兰表达式，在编译程序对我们书写的程序中的表达式进行语法检查时，往往就可以通过逆波兰表达式进行。我们所要设计并实现的程序就是将中缀表示的算术表达式转换成后缀表示，例如，将中缀表达式(A-(B*C+D)*E)/(F+G)转换为后缀表示为：ABC*D+E*--FG+/
* 
* 注意：为了简化编程实现，假定变量名均为单个字母，运算符只有+，-，*，/ 和^（指数运算），可以处理圆括号()，并假定输入的算术表达式正确。
* 
* 要求：使用栈数据结构实现 ，输入的中缀表达式以＃号结束
* 
* 输入
*   整数N，表示下面有N个中缀表达式
*   N个由单个字母、整数和运算符构成的表达式
* 
* 输出
*   N个后缀表达式。
*/

#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 1000

struct SqStack {
    char *base;
    char *top;
    int stacksize;
};

void InitStack (SqStack &s) {
    s.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
}

void push(SqStack &s,char e) {
    *(s.top)++=e;
}

void pop(SqStack &s) {
    if(s.top==s.base) return;
    *(s.top)--;
}

void ClearStack(SqStack &s) {
    s.top=s.base;
}

int EmptyStack( SqStack &s) {
    if(s.top==s.base)
        return 0;
    else
        return 1;
}

char GetTop(SqStack &s) {
    if(s.top>s.base)
        return *(s.top-1);
    else return 0;
}

int COMP(char a,char b) {
    int x,y;

    switch(a) {                 
        case '^':{x = 4;break;}
        case '*':{x = 3;break;}
        case '/':{x = 3;break;}
        case '+':{x = 2;break;}
        case '-':{x = 2;break;}
    }

    switch(b) {                 
        case '^':{y = 4;break;}
        case '*':{y = 3;break;}
        case '/':{y = 3;break;}
        case '+':{y = 2;break;}
        case '-':{y = 2;break;}
        case '(':{y = 1;break;}
    }

    if(x>y) 
        return 1;
    else 
        return 0;
}

int main() {
    struct SqStack st;
    InitStack(st);
    int N,i,flag=0;
    char c,temp1,temp2;
    scanf("%d",&N);
    getchar();
    for ( i=0 ; i<N ; i++ ) {
        while ( (c=getchar()) != '\n' ) {    
            if(((c>'a'||c=='a')&&(c<'z'||c=='z'))||((c>'A'||c=='A')&&(c<'Z'||c=='Z'))||((c>'0'||c=='0')&&(c<'9'||c=='9'))) {
                printf("%c",c);
                flag=0;
                continue;
            }

            else if ( flag == 1 && c == '-' ) {
                printf("%c",c);
                continue;
            }

            else if ( c == '#' ) 
                continue;
            else {
                if (c=='('||c=='^') {
                    push(st,c);
                    flag=1;
                }
                else if ( c=='+'||(flag==0&&c=='-')||c=='*'||c=='/' ) {
                    while (1) {
                        if (EmptyStack(st)==0) {
                            push(st,c);
                            break;
                        }
                        temp2=GetTop(st);
                        if (COMP(c,temp2)==1) { 
                            push(st,c);
                            break;
                        }
                        else {
                            while (COMP(c,temp2)!=1&&EmptyStack(st)!=0) {
                                printf("%c",temp2);
                                pop(st);
                                temp2=GetTop(st);
                            }
                            push(st,c);
                            break;
                        }
                    }
                    flag=1;
                }

                else {
                    temp1=GetTop(st);
                    while ( temp1 != '(' ) {
                        printf("%c",temp1);
                        pop(st);
                        temp1=GetTop(st);
                    }
                    pop(st);
                    flag=0;
                }
            }    
        }
        
        while ( EmptyStack(st) != 0 ) {
            temp1=GetTop(st);
            printf("%c",temp1);
            pop(st);
        }

        printf("\n");
        ClearStack(st);
    }
    
    return 0;
}