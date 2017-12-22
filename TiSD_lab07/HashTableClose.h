#ifndef TISD7_HASHTABLECLOSE_H
#define TISD7_HASHTABLECLOSE_H

#include "library.h"

template<class T>
class HashTableClose
{
private:
	T *table;
	short int *status;
	int tableSize;
	int count_of_elem;
public:
	HashTableClose(int Start_size);

	~HashTableClose();

	void New_Table(int new_size);

	bool Insert(T k);

	bool Search(T x);

	int Memory();

	bool Delete_element(T x);

	void Show();
};

#endif //TISD7_HASHTABLECLOSE_H
