//
// Created by Islam, Abdullah Al Raqibul on 1/30/20.
//

#ifndef UTILLS_H
#define UTILLS_H

#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

int _abs(int a) {
    return a < 0 ? -a : a;
}

int _min(int a, int b) {
    return a < b ? a : b;
}

int _max(int a, int b) {
    return a > b ? a : b;
}

void UsageMessage(const char *command) {
    cout << "Usage: " << command << " [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -threads n: execute using n threads (default: 1)" << endl;
    cout << "  -db dbname: specify the name of the DB to use (default: basic)" << endl;
    cout << "  -P propertyfile: load properties from the given file. Multiple files can" << endl;
    cout << "                   be specified, and will be processed in the order specified" << endl;
}

inline bool StrStartWith(const char *str, const char *pre) {
    return strncmp(str, pre, strlen(pre)) == 0;
}

#endif //UTILLS_H
