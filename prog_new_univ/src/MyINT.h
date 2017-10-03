#ifndef My_INT_H
#define My_INT_H

#include <iostream>
#include <fstream>
#include <vector>
#include "CONSTANT.h"

using namespace std;

struct MyINT {
	MyINT(const int& size) {
		data.resize(size, 0);
	}
	MyINT(){
		data.resize(MAX_COUNT, 0);
	}
	int count = 0;
	vector<int> data;
	bool sign = false;
	int error_input = 0;
};

struct MyINT;
istream& operator>> (istream &stream, MyINT &number);

#endif //My_INT_H
