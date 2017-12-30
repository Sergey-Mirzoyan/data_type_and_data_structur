#ifndef TISD7_BST_H
#define TISD7_BST_H

#include "library.h"

template<typename T>
struct element
{
	T key;
	element *left = NULL;
	element *right = NULL;

	element(T x)
	{
		key = T(x);
		left = NULL;
		right = NULL;
	}

};


template<typename T>
class BST
{
private:
	element<T> *head = NULL;
	int count_of_element = 0;

	void delete_tree(element<T> *tmp);

	void operator_copy(element<T> **head, element<T> *tmp);

	void delete_remove(element<T> *prev, element<T> *tmp);

public:
	BST();

	BST(const BST &obj);

	BST<T> &operator=(const BST &obj);

	int Memory();

	void Insert(T x);

	bool Remove(T x);

	bool Search(T x);

	~BST();

	template<typename X>
	friend void print(X *tmp, int deep, bool flag);

	template<typename X>
	friend void show_as_tree(X *tree);

	template<typename X>
	friend void show(X *tree);

};


#endif //TISD7_BST_H
