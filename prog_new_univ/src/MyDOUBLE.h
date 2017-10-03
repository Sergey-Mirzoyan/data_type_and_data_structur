#ifndef My_DOUBLE_H
#define My_DOUBLE_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "CONSTANT.h"

using namespace std;


struct MyDOUBLE {
	MyDOUBLE(const int& size) {
		data.resize(size, 0);
	}
	MyDOUBLE(){
		data.resize(MAX_COUNT+2, 0);
	}
	int count = 0;
	vector<int> data;
	int exp = 0;
	bool sign = false;
	int error_input = 0;
};

struct MyDOUBLE;
istream& operator>> (istream &stream, MyDOUBLE &number);
ostream& operator<<(ostream &stream, const MyDOUBLE &obj);
MyDOUBLE operator/ (const MyINT &a, const MyDOUBLE &b);

#endif //My_DOUBLE_H
