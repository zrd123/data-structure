#pragma once

#include <string>
using std::string;

class matchMode {
private:
	string* main, *mode;
	int* next;
public:
	matchMode();
	void setString(const string& str);
	void setMode(const string& str);
	int KMP() const;
	int match() const;
private:
	void getNext();
};