#ifndef TISD7_HASHTABLEOPEN_H
#define TISD7_HASHTABLEOPEN_H

#include "library.h"

template<typename T>
struct ElementTable
{
    T value;
    ElementTable<T> *next = NULL;

    ElementTable(){}
    ElementTable(T x)
    {
        value = x;
        next = NULL;
    }
};

template<class T>
class HashTableOpen
{
private:
    ElementTable<T> **table;
    bool *status;
    int tableSize;
    int count_of_elem;
public:
    HashTableOpen(int Start_size);
    ~HashTableOpen();
    void New_Table(int new_size);
    bool Insert(T k);
    bool Search(T x);
    int Memory();
    bool Delete_element(T x);
    void Show();
};

#endif //TISD7_HASHTABLEOPEN_H
