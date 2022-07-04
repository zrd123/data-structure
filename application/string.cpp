#include "string.h"
#include <iostream>

matchMode::matchMode(const string& main, const string& mode) {
    this->main = new string(main);
    this->mode = new string(mode);
    getNext();
}

matchMode::~matchMode() {
    delete main, mode;
    if(next)
        delete next;
}

void matchMode::getNext() {
    if (*main == "") {
        next = nullptr;
    }
    else {
        if (next) {
            delete next;
            next = nullptr;
        }
        next = new int[mode->length()];
        next[0] = -1;           //while the first char not match, i++,j++
        int j = 0, k = -1;
        while (j < (int)(mode->length()) - 1) { // -1 防止溢出
            if (k == -1 || mode->at(j) == mode->at(k)) {
                if (next[++j] == next[++k]) {
                    next[j] = next[k];
                }
                else {
                    next[j] = k;
                }
            }
            else {
                k = next[k];
            }
        }
    }
    //for (int i = 0; i < mode->length(); ++i) {
    //    std::cout << next[i] << " ";
    //}
    //std::cout << std::endl;
}

void matchMode::setString(const string& str) {
	*main = str;
}

void matchMode::setMode(const string& str) {
    *mode = str;
    getNext();
}

int matchMode::KMP() const {
    int i = 0;
    int j = 0;
    while (i < (int)main->length() && j < (int)mode->length()) {
        if (j == -1 || main->at(i) == mode->at(j)) {
            ++i;++j;
        }
        else{
            j = next[j];
        }
    }
    if (j == (int)mode->length()) {
        return i - j;
    }
    return -1;
}

int matchMode::match() const {
    int i = 0;
    int j = 0;
    while (i < (int)main->length() && j < (int)mode->length()) {
        if (main->at(i) == mode->at(j)) {
            ++i; ++j;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= mode->length()) {
        return i - j;
    }
    return -1;
}