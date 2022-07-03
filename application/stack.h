#pragma once

#include <stack>
#include <string>
using std::stack;
using std::string;

class ExpressionCalcuate {
private:
	string prefix;	//前缀
	string infix;	//中缀
	string suffix;	//后缀

public:
	void setPrefix(const string& prefix);
	void setSuffix(const string& suffix);
	void setInfix(const string& infix);
	string getPrefix() const;
	string getSuffix() const;
	string getInfix() const;
	bool infixToPrefix();				//中缀转前缀
	bool infixToSuffix();				//中缀转后缀
	int calcuatePrefix();				//前缀计算
	int calcuateSuffix();				//后缀计算
	int calcuateInfix();				//中缀计算
	bool calcuateOnce(stack<int>& numStack, stack<char>& signStack);
};

bool bracketCheck(char* str, int length);
