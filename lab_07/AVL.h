#ifndef TISD7_AVL_H
#define TISD7_AVL_H

#include "library.h"

template<typename T>
struct AVL_Node
{
	AVL_Node *left, *right;
	T key;
	int h;
	int cnt;

	//Конструктор по умолчанию
	AVL_Node()
	{
		left = right = NULL;
		h = cnt = 0;
	}

	//Конструктор
	AVL_Node(T &x)
	{
		left = right = NULL;
		key = x;
		h = cnt = 1;
	}
};

template<typename T>
class AVL
{
private:
	int height(AVL_Node<T> *t);

	int difference_of_h(AVL_Node<T> *t);

	int cnt_value(AVL_Node<T> *t);

	T key_value(AVL_Node<T> *t);

	void right(AVL_Node<T> *&t);

	void left(AVL_Node<T> *&t);

	void balance(AVL_Node<T> *&t); // балансировка узла p
	void add_to_avl(AVL_Node<T> *&t, AVL_Node<T> *tmp);

	AVL_Node<T> *findmin(AVL_Node<T> *t);

	AVL_Node<T> *removemin(AVL_Node<T> *t);

	bool delete_from_avl(AVL_Node<T> *&t, T x);

	//int value_by_index(AVL_Node* t, int ind);
	//int index(AVL_Node* t, int x);
	void free_tree(AVL_Node<T> *&tmp);

	AVL_Node<T> *head = NULL;
	int count_of_element = 0;
public:
	AVL() {}

	int Memory();

	void Insert(T x);

	bool Remove(T x);

	bool Search(T x);

	~AVL();

	template<typename X>
	friend void print(X *tmp, int deep, bool flag);

	template<typename X>
	friend void show_as_tree(X *tree);

	template<typename X>
	friend void show(X *tree);
};


#endif //TISD7_AVL_H
