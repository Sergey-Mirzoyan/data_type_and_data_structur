#ifndef __BOOK__H__
#define __BOOK__H__

#include <iostream>
#include <string>
#include <fstream>

#define LEN_STRING 1024

using namespace std;

struct book_t
{
	book_t(){};

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
    //void delite_book();
};

void readFromFile(ifstream &file, book_t *array, int count_buses);
void delet(ifstream &stream, book_t *array);

struct List_Book
{
	int count_books;
	book_t *head;
};
/*
#define LEN_STRING 150
#include <iostream>

using namespace std;

enum kind_art {
    novels, plays, poems
};

enum kind_localization {
    patriotic, translated
};

enum type_book {
    technical, art
};

struct technical_book {
    char industry[LEN_STRING];
    kind_localization locate;
    int year;

    void create_technical_book();

    void show();

};

struct art_book {
    kind_art art;

    void create_art_book();

    void show();
};


union kind_book {
    technical_book tech;
    art_book art;
};

class Book {

private:

    string author_name;
    string book_title;
    string publisher;
    int pages;
    type_book book_t;
    kind_book book_record;

public:

    void read_from_file(istream &fin);

    bool search(int year, char *ind);

    void create_record();

    void show();

    int GetPages();

};
*/
#endif //__BOOK__H__
