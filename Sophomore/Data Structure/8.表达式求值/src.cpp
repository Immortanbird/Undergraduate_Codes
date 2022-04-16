/* 
* 要求：
* 采用算符优先算法，计算的中间结果只保留整数。
* 
* 输入：
*   第一行为整数N。表示下面有N个表达式
*   从第二行起的后面N行为N个由整数构成的表达式
* 
* 输出：
*   共N行，每行为相应表达式的计算结果。
*   如果判断出表达式有错误，则输出error.
*   如果在计算过程中出现除数为0的情况，则输出：Divide 0.

* 特殊情况说明：
*   在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
*       10加-8表示为：10+-8。
*       10减-8表示为：10--8。
*/

#include "stdio.h"
#include "string.h"
#include "math.h"
#define MAX 9999999

int figure[100];
char symbol[100];
int topf = -1, tops = -1;
char operation[9] = {'+','-','*','/','(',')','#','^','%'};
char checklist[9][9] = {
	       /*+   -   *   /   (   )   #   ^   %*/
	/* + */{'>','>','<','<','<','>','>','<','<'},
	/* - */{'>','>','<','<','<','>','>','<','<'},
	/* * */{'>','>','>','>','<','>','>','<','>'},
	/* / */{'>','>','>','>','<','>','>','<','>'},
	/* ( */{'<','<','<','<','<','=',' ','<','<'},
	/* ) */{'>','>','>','>',' ','>','>','>','>'},
	/* # */{'<','<','<','<','<',' ','=','<','<'},
	/* ^ */{'>','>','>','>','<','>','>','<','>'},
	/* % */{'>','>','>','>','<','>','>','<','>'}
};
int number(char *q) {
	return (int)(*q - '0');
}

void push_figure(int q) {
	figure[++topf] = q;
}

int pop_figure() {
	return figure[topf--];
}

char pop_symbol() {
	return symbol[tops--];
}

void push_symbol(char ch) {
	symbol[++tops] = ch;
}

int operate(int x, int y, char symbol) {
	switch(symbol) {
		case '+':
			return x+y;
		case '-':
			return x-y;
		case '*':
			return x*y;
		case '/':
			if(y) return x/y;
			else {
				printf("Divide 0.\n");
				return MAX;
			}
		case '%':
			return (int)fmod(x,y);
		case '^':
			if(y>=0) return (int) pow(x,y);
			else {
				printf("error.\n");
				return MAX;
			}
		default:
			printf("error.\n");
			return MAX;
	}
}

char compare(char x, char y) {
	int a, b, i;
	for(i = 0; i <= 8; i++) {
		if(operation[i] == x) {
			a = i;
			break;
		}
	}
	for(i = 0; i <= 8; i++) {
		if(operation[i] == y) {
			b = i;
			break;
		}
	}
	return checklist[a][b];
}
int In(char c) {
	switch(c) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case '=':
		case '^':
		case '%':
			return 1;
		default:
			return 0;
	}

}
int main(int argc, char *argv[]) {
	int n, flag = 0, sign, flag1 = 0;
	char expression[100], *p;
	scanf("%d",&n);
	while(n--) {
		sign = 1;
		flag = 2;
		scanf("%s",expression);
		strcat(expression, "#");
		p = expression;
		push_symbol('#');
		while(*p != '#' || symbol[tops] != '#') {
			if(*p == '-' && (In(*(p-1))||p==expression) ) {
				//flag1 = 1;
				push_figure(-1);
				push_symbol('*');
				p++;
			}
			if(*p >='0' && *p <= '9' /*&& flag1 == 0*/) {
				if(flag == 0) {
					push_figure(pop_figure()*10+number(p++));
					flag = 0;
				} else
					push_figure(number(p++));
				flag = 0;
			} 
//			else if(*p >='0' && *p <= '9' /*&& flag1 == 1*/) {
//				if(flag == 0) {
//					push_figure(pop_figure()*10-number(p++));
//					flag = 0;
//				} else
//					push_figure(-1*number(p++));
//				flag = 0;
//			} 
			else {
				if(flag == 1) {
					if(*p == '+' || *p == '*' || *p == '/' || *p == '%' ||*p == '^') {
						printf("error.\n");
						sign = 0;
						break;
					}
				}
				if(*p == '(') flag = 1;
				else flag = 2;

				if(tops == -1) {
					printf("error.\n");
					sign = 0;
					break;
				} else {
					char ch = pop_symbol(), ans;
					ans = compare(ch, *p);
					if(ans == ' ') {
						printf("error.\n");
						sign = 0;
						break;
					} else if(ans == '<') {
						push_symbol(ch);
						push_symbol(*p++);
					} else if(ans == '=') {
						p++;
					} else {
						int integer_x, integer_y;
						integer_y = pop_figure();
						integer_x = pop_figure();
						int judge = operate(integer_x, integer_y, ch);
						if(judge == MAX) {
							sign = 0;
							break;
						} else	push_figure(judge);
						continue;
					}
				}
			}
		}
		if (sign) {
			if(topf == 0 && tops == 0) printf("%d\n",figure[topf]);
			else {
				printf("error.\n");
			}
		}
		memset(expression,'\0',100);
		topf = -1;
		tops = -1;
	}
	return 0;
}