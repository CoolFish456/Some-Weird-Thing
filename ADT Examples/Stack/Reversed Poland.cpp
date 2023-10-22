#include <iostream>
#include <stack>
using namespace std;
//没写完
int main() {
	char Exp[100] = {0}, temp;
	stack<char> Opr;
	scanf("%s", Exp);
	for (int i = 0; Exp[i] != 0; i++) {
		switch (Exp[i]) {
			case ' ':
				break;
			case '+':
				if (!Opr.empty()) {
					if (Opr.top() == '*' || Opr.top() == '+') {
						temp = Opr.top();
						Opr.pop();
						Opr.push(Exp[i]);
						printf("%c", temp);
					}
					else Opr.push(Exp[i]);
				} else
					Opr.push(Exp[i]);
				break;
			case '*':
				if (!Opr.empty()) {
					if (Opr.top() == '*') {
						temp = Opr.top();
						Opr.pop();
						Opr.push(Exp[i]);
						printf("%c", temp);
					} else
						Opr.push(Exp[i]);
				} else
					Opr.push(Exp[i]);
				break;
			case '(':
				Opr.push(Exp[i]);
				break;
			case ')':
				do {
					temp = Opr.top();
					Opr.pop();
					printf("%c", temp);
				}while (Opr.top() != '(');
				Opr.pop();
				break;
			default:
				printf("%c", Exp[i]);
				break;
		}
	}
	while (!Opr.empty()) {
		temp = Opr.top();
		printf("%c", temp);
		Opr.pop();
	}
	return 0;
}