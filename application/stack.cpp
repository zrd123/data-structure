#include "stack.h"
#include <iostream>
#include <stdexcept>
void ExpressionCalcuate::setPrefix(const string& prefix) {
	this->prefix = prefix;
}

void ExpressionCalcuate::setSuffix(const string& suffix) {
	this->suffix = suffix;
}

void ExpressionCalcuate::setInfix(const string& infix) {
	this->infix = infix;
}

string ExpressionCalcuate::getPrefix() const {
	return this->prefix;
}

string ExpressionCalcuate::getSuffix() const {
	return this->suffix;
}

string ExpressionCalcuate::getInfix() const {
	return this->infix;
}

bool ExpressionCalcuate::infixToPrefix() {
	stack<char> signStack, res;
	string result = "";
	for (int i = (int)(infix.size() - 1); i >= 0; --i) {
		char c = infix[i];
		if (c >= '0' && c <= '9') {
			res.push(c);
		}
		else if (c == '+' || c == '-') {
			bool flag = true;
			while (flag) {
				//栈顶为 非运算符 或 优先级非大于自身的运算符
/*				if (signStack.empty() || signStack.top() == ')' ||
					signStack.top() == '+' || signStack.top() == '-')*/
				if (signStack.empty() || signStack.top() == ')') {
					signStack.push(c);
					flag = false;
				}
				//栈顶为优先级大于自身的运算符 * /
				else {
					try {
						res.push(signStack.top());
						signStack.pop();
					}
					catch (std::exception& e) {
						std::cerr << e.what() << "pop() exception" << std::endl;
					}
				}
			}
		}
		else if (c == '*' || c == '/') {
			bool flag = true;
			while (flag) {
				//栈顶为 非运算符 或 优先级非大于自身的运算符
				if (signStack.empty() || signStack.top() == ')' ||
					signStack.top() == '+' || signStack.top() == '-' ||
					signStack.top() == '/' || signStack.top() == '*') {
					signStack.push(c);
					flag = false;
				}
				//栈顶为优先级大于自身的运算符 * / 基本不执行(除了次方)
				else {
					res.push(signStack.top());
					signStack.pop();
				}
			}
		}
		else if (c == ')') {
			signStack.push(c);
		}
		else if (c == '(') {
			try {
				while (signStack.top() != ')') {
					res.push(signStack.top());
					signStack.pop();
				}
				signStack.pop();
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\nin file of stack about function infixToprefix()!!" << std::endl;
				exit(1);
			}
		}

	}
	while (!signStack.empty()) {
		res.push(signStack.top());
		signStack.pop();
	}
	while (!res.empty()) {
		result += res.top();
		res.pop();
	}
	this->prefix = result;
	return true;

}

bool ExpressionCalcuate::infixToSuffix() {
	stack<char> signStack;
	string result = "";
	for (size_t i = 0; i < infix.size(); ++i) {
		char c = infix[i];
		if (c >= '0' && c <= '9') {
			result += c;
		}
		else if (c == '+' || c == '-') {
			bool flag = true;
			while (flag) {
				//栈顶为优先级小于自己的运算符或非运算符
				if (signStack.empty() || signStack.top() == '(') {
					signStack.push(c);
					flag = false;
				}
				//弹出优先级大于等于自己的运算符 + - * /
				else {
					try {
						result += signStack.top();
						signStack.pop();
					}
					catch (std::exception& e) {
						std::cerr << e.what() << "\npop() exception!!" << std::endl;
					}
				}
			}
		}
		else if (c == '*' || c == '/') {
			bool flag = true;
			while (flag) {
				//栈顶为优先级小于自己的运算符或非运算符
				if (signStack.empty() || signStack.top() == '(' ||
					signStack.top() == '+' || signStack.top() == '-') {
					signStack.push(c);
					flag = false;
				}
				//弹出优先级大于等于自己的运算符 * /
				else {
					try {
						result += signStack.top();
						signStack.pop();
					}
					catch (std::exception& e) {
						std::cerr << e.what() << "\npop() exception!!" << std::endl;
					}
				}
			}
		}
		else if (c == '(') {
			signStack.push(c);
		}
		else if (c == ')') {
			try {
				while (signStack.top() != '(') {
					result += signStack.top();
					signStack.pop();
				}
				signStack.pop();
			}
			catch (std::exception &e ) {
				std::cerr << e.what() << "\nin file of stack about function infixToSuffix()!!" << std::endl;
				exit(1);
			}
		}
	}
	while (!signStack.empty()) {
		result += signStack.top();
		signStack.pop();
	}
	this->suffix = result;
	return true;
}

int ExpressionCalcuate::calcuatePrefix() {
	stack<int> numStack;
	for (int i = (int)(prefix.size() - 1); i >= 0; --i) {
		char c = prefix[i];
		if (c >= '0' && c <= '9') {
			int num = c - '0';
			numStack.push(num);
		}
		else {
			int a = numStack.top();
			numStack.pop();
			int b = numStack.top();
			numStack.pop();
			if (c == '+') {
				numStack.push(a + b);
			}
			else if (c == '-') {
				numStack.push(a - b);
			}
			else if (c == '*') {
				numStack.push(a * b);
			}
			else if (c == '/') {
				numStack.push(a / b);
			}
		}

	}
	return numStack.top();
}

int ExpressionCalcuate::calcuateSuffix() {
	stack<int> numStack;
	for (size_t i = 0; i < suffix.size(); ++i) {
		char c = suffix[i];
		if (c >= '0' && c <= '9') {
			int num = c - '0';
			numStack.push(num);
		}
		else {
			int b = numStack.top();
			numStack.pop();
			int a = numStack.top();
			numStack.pop();
			if (c == '+') {
				numStack.push(a + b);
			}
			else if (c == '-') {
				numStack.push(a - b);
			}
			else if (c == '*') {
				numStack.push(a * b);
			}
			else if (c == '/') {
				numStack.push(a / b);
			}
		}

	}
	return numStack.top();
}

int ExpressionCalcuate::calcuateInfix() {
	stack<int> numStack;
	stack<char> signStack;
	for (size_t i = 0; i < infix.size(); ++i) {
		char c = infix[i];
		if (c >= '0' && c <= '9') {
			int num = c - '0';
			numStack.push(num);
		}
		else if (c == '+') {
			bool flag = true;
			while (flag) {
				if (signStack.empty() || signStack.top() == '(') {
					signStack.push(c);
					flag = false;
				}
				else {
					calcuateOnce(numStack, signStack);
				}
			}
		}
		else if (c == '-') {
			bool flag = true;
			while (flag) {
				if (signStack.empty() || signStack.top() == '(' || signStack.top() == '+') {
					signStack.push(c);
					flag = false;
				}
				else {
					calcuateOnce(numStack, signStack);
				}
			}
		}
		else if (c == '*') {
			bool flag = true;
			while (flag) {
				if (signStack.empty() || signStack.top() == '(' ||
					signStack.top() == '+' || signStack.top() == '-') {
					signStack.push(c);
					flag = false;
				}
				else {
					calcuateOnce(numStack, signStack);
				}
			}
		}
		else if (c == '/') {
			bool flag = true;
			while (flag) {
				if (signStack.empty() || signStack.top() == '(' ||
					signStack.top() == '+' || signStack.top() == '-' || signStack.top() == '*') {
					signStack.push(c);
					flag = false;
				}
				else {
					calcuateOnce(numStack, signStack);
				}
			}
		}
		else if (c == '(') {
			signStack.push(c);
		}
		else if (c == ')') {
			while (signStack.top() != '(') {
				calcuateOnce(numStack, signStack);
			}
			signStack.pop();
		}
	}
	while (!signStack.empty()) {
		calcuateOnce(numStack, signStack);
	}
	return numStack.top();
}

bool ExpressionCalcuate::calcuateOnce(stack<int>& numStack, stack<char>& signStack) {
	int b = numStack.top();
	numStack.pop();
	int a = numStack.top();
	numStack.pop();
	char c = signStack.top();
	signStack.pop();
	if (c == '+') {
		numStack.push(a + b);
	}
	else if (c == '-') {
		numStack.push(a - b);
	}
	else if (c == '*') {
		numStack.push(a * b);
	}
	else if (c == '/') {
		numStack.push(a / b);
	}
	return true;
}


bool bracketCheck(char* str, int length) {
	stack<char> check;
	for (int i = 0; i < length; ++i) {
		if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
			check.emplace(str[i]);
		}
		else {
			if (check.empty()) {
				return false;
			}

			char topElem = check.top();
			check.pop();
			if (str[i] = ')' && topElem != '(') {
				return false;
			}
			if (str[i] = ']' && topElem != '[') {
				return false;
			}
			if (str[i] = '}' && topElem != '{') {
				return false;
			}
		}
	}
	return check.empty();
}