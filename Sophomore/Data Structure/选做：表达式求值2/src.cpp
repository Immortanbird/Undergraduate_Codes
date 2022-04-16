/* 
* 问题描述
*   带有变量的中缀表达式是常见的数学表达式。如果规定变量由长度不超过 8 个小写字母组成；end为保留字，表示程序段结束；用？表示输出指定变量的值，则可以设计出比较复杂的表达式（即一个可顺序执行语句序列）。例如，如果有如下语句段：
*   abc=10
*   def=8
*   c=abc+def
*   abc=abc+5-c*2
*   ? c
*   ? abc
*   end
* 则输出为：
*   c=18
*   abc=-21
* 
* 注意：为了简化编程实现，运算符只有＋，－，＊，／ ，%和＾（指数运算），可以处理圆括号（），并假定输入的算术表达式正确。
* 
* 要求：使用栈结构实现。
* 
* 输入：表达式序列
* 
* 输出：全部指定变量的值
* 
* 表达式中的全部计算结果均为整数。如果在计算过程中出现除数为0的情况，则输出：Divide 0.
* 
* 特殊情况说明：
*   在表达式中，如果操作数出现负数（例如-8），则要特别注意。例如：
*   10加-8表示为：10+-8。
*   10减-8表示为：10--8。
*/

#include<cstdio>
#include<string>
#include<map>
#include<stack>
#include<math.h>
#include<iostream>

using namespace std;

map<string, int> Varible;
stack<char> sta;
stack<int>  sta_num;
string Instruction;
string tmp;

int GetproiIncoming(char c) {
	switch (c) {
		case('+') :return 3;
		case('-') :return 3;
		case('*') :return 5;
		case('/') :return 5;
		case('%') :return 5;
		case('(') :return 10;
		case('^') :return 8;
	}
}

int GetproInstack(char c) {
	switch (c) {
		case('+') :return 4;
		case('-') :return 4;
		case('*') :return 6;
		case('/') :return 6;
		case('%') :return 6;
		case('(') :return 1;
		case('^') :return 7;
	}
}

int comput(char c, int a, int b) {
	switch (c) {
		case('+') :return a+b;
		case('-') :return a-b;
		case('*') :return a*b;
		case('/') :return a/b;
		case('%') :return a%b;
		case('^') :return (int)pow(double(a),double(b));
	}
}

int Getvar(string tmp) {
	int num = 0;
	for (int i=0; tmp[i]; i++) {
		if (tmp[i] >= '0' && tmp[i] <= '9') {
			num = num*10 + tmp[i] - '0';
		} else if (tmp[i]>='a' && tmp[i]<='z') {
			string var;
			int k = i;
			while (tmp[k]>='a' && tmp[k]<='z') {
				k++;
			}
			var = tmp.substr(i, k-i);
			sta_num.push(Varible[var]);
			i = k - 1;
		} else if (!(tmp[i]>='0' && tmp[i]<='9') && !(tmp[i]>='a' && tmp[i]<='z')) {
			if (tmp[i] == '=') continue;
			if ((tmp[i-1] >= '0' && tmp[i-1] <= '9')) {
				sta_num.push(num);
				num = 0;
			} else if (!(tmp[i-1]>='0'&&tmp[i-1]<='9') && !(tmp[i-1]>='a'&&tmp[i-1]<='z')&&(tmp[i]=='+'||tmp[i]=='-')) {
				i++;
				int k = i;
				while (tmp[k] && (tmp[k]>='0'&&tmp[k]<='9')) {
					num = num * 10 + tmp[k] - '0';
					k++;
				}
				if (tmp[i - 1] == '-') num *= -1;
				i = k - 1;
				continue;
			}
			if (sta.empty()||tmp[i]=='(') {
				sta.push(tmp[i]);
				continue;
			} else if (tmp[i] == ')') {
				char op;
				while (!sta.empty() && (op = sta.top()) != '(') {
					int b = sta_num.top();
					sta_num.pop();
					int a = sta_num.top();
					sta_num.pop();
					if (b == 0 && op == '/')
						continue;
					else {
						sta_num.push(comput(op,a,b));
					}
					sta.pop();
				}
				sta.pop();
			} else {
				int Incoming = GetproiIncoming(tmp[i]);
				int Instack;
				char op;
				while (!sta.empty()&&(Instack = GetproInstack(sta.top())) > Incoming) {
					op = sta.top();
					int b = sta_num.top();
					sta_num.pop();
					int a = sta_num.top();
					sta_num.pop();
					if (b == 0 && op == '/')
						continue;
					else {
						sta_num.push(comput(op, a, b));
					}
					sta.pop();
				}
				sta.push(tmp[i]);
			}
		}
	}
	if (tmp[tmp.length()-1] >= '0'&&tmp[tmp.length()-1] <= '9')
		sta_num.push(num);
	if (!sta.empty()||!sta_num.empty()) {
		while (!sta.empty()) {
			char op = sta.top();
			int b = sta_num.top();
			sta_num.pop();
			int a = sta_num.top();
			sta_num.pop();
			if (b == 0 && op == '/')
				continue;
			else {
				sta_num.push(comput(op, a, b));
			}
			sta.pop();
		}
		return sta_num.top();
	} else return num;
}
int main() {
	//freopen("num.txt", "r", stdin);
	while (getline(cin,Instruction)) {
		if (Instruction == "end")
			break;
		while (!sta.empty())
			sta.pop();
		while (!sta_num.empty())
			sta_num.pop();
		if (Instruction[0] == '?') {
			tmp = Instruction.substr(2);
			int num = Varible.find(tmp)->second;
			cout << tmp<< '='<<num<< endl;
		} else if (Instruction[0] >= 'a' && Instruction[0] <= 'z') {
			int i = 0;
			string varble;
			while (Instruction[i] != '=') {
				i++;
			}
			varble = Instruction.substr(0, i);
			if (Varible.count(varble) == 0) {
				Varible[varble] = 0;

			}
			string tmp = Instruction.substr(i);
			Varible[varble] = Getvar(tmp);
		}
	}
	return 0;
}