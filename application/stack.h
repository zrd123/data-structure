#pragma once

#include <stack>
using std::stack;

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