#include "string.h"

void matchMode::getNext() {
    int* next = new int[mode->length()];
    next[0] = -1;           //while the first char not match, i++,j++
    int j = 0;
    int k = -1;
    while (j < (int)(mode->length()) - 1) {
        if (k == -1 || mode[j] == mode[k]) {
            j++;
            k++;
            next[j] = k;
        }
        else {
            k = next[k];
        }
    }
}

void matchMode::setString(const string& str) {
	*main = str;
}

void matchMode::setMode(const string& str) {
    *mode = str;
}

int matchMode::KMP() const {
    int i = 0;
    int j = 0;
    while (i < (int)main->length() && j < (int)mode->length() ) {
        if (j == -1 || main[i] == mode[j]) {
            ++i;
            ++j;
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
        if (main[i] == mode[j]) {
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