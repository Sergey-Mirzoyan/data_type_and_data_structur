#ifndef __TABLE__KEY__H__
#define __TABLE__KEY__H__

#include "Book.h"

class Table_key {
public:
    int id;
    string name_book;

    Table_key() {
        id = 0;
        name_book = '\0';
    }

    Table_key(int i, book_t &obj) {
        id = i;
        name_book = obj.name_book;
    }

};

#endif //__TABLE__KEY__H__
