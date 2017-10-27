#ifndef __BOOK__H__
#define __BOOK__H__

#include <iostream>
#include <string>
#include <fstream>

#define LEN_STRING 1024

using namespace std;

struct book_t
{
	book_t()
	{
		author_name = '\0';
		name_book = '\0';
		publ_office = '\0';
		pages = 0;
		bool_type_book = -1;
	};

	string author_name;
	string name_book;
	string publ_office;
    int pages;
    int bool_type_book;

    union
	{
    	struct
    	{
    		char industry[LEN_STRING];
    	    int Russian;
    	    int publ_date;
    	}tech_book;

    	struct
    	{
    	    char genre[LEN_STRING];
    	}fict_book;
    }t_book;

    void create_book(istream& stream);//create_record
    void show(void) const;
    void read_from_file(istream& file);
    bool search(int year, char *ind);
};

void readFromFile(ifstream &file, book_t *array, int count_buses);
void delet(ifstream &stream, book_t *array);

#endif //__BOOK__H__
