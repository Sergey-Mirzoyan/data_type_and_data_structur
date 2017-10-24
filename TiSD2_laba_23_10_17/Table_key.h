#ifndef __TABLE__KEY__H__
#define __TABLE__KEY__H__

#include "Book.h"

class Table_key {
public:
    int id;
    int pages;

    Table_key() {
        id = 0;
        pages= 0;
    }

    Table_key(int i, book_t &obj) {
        id = i;
        pages = obj.pages;
    }

};

#endif //__TABLE__KEY__H__
