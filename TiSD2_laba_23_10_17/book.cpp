#include <iostream>
#include <climits>
#include <cstring>
#include <limits>
#include <sstream>

#include "book.h"

using namespace std;

void readFromFile(ifstream &file, book_t *array, int count_buses)
{
	for (int i = 0; i < count_buses; i++, array++)
	{
		file >> array->author_name;
		file >> array->name_book;
		file >> array->publ_office;
		file >> array->pages;

		file >> array->bool_type_book;
		if (!array->bool_type_book)
		{
			file >> array->t_book.tech_book.industry;
			file >> array->t_book.tech_book.Russian;
			file >> array->t_book.tech_book.publ_date;

		}
		else
		{
			file >> array->t_book.fict_book.genre;
		}
	}
}

void book_t::show(void) const
{
    cout << "Автор: " << author_name << endl;
    cout << "Название: " << name_book << endl;
    cout << "Издательство: " << publ_office << endl;
    cout << "Кол-во страниц: " << pages << endl;

    cout << "Вид литературы: ";
    switch (bool_type_book)
    {
        case 0:
            cout << "Техническая" << endl;

			cout << "Отрасль: " << t_book.tech_book.industry << endl;

			cout << "Тип  произведения: ";
			switch (t_book.tech_book.Russian)
			{
				case 0:
					cout << "отечественная" << endl;
					break;
				case 1:
					cout << "переводная" << endl;
					break;
			}

			cout << "Год издания: " << t_book.tech_book.publ_date << endl;
            break;
        case 1:
            cout << "Художественная" << endl;
			cout << "Тип  произведения: " << t_book.fict_book.genre << endl;
            break;
    }
}

void book_t::create_book(istream& stream)
{
	author_name = "";
    cout << "Введите автора: ";
    stream >> author_name;


    name_book = "";
    cout << "Введите название: ";
    stream >>name_book;


    publ_office = "";
    cout << "Введите издательство: ";
    stream >> publ_office;


    pages = 0;
    while (pages <= 0)
    {
    	cout << "Введите количество страниц: ";
    	stream >> pages;
    	if (!cin || pages <= 0)
		{
    		cin.clear();
    		while (cin.get() != '\n');
    		cout << "Ошибочный ввод" << endl;
    	}
    }

    bool_type_book = -1;
    while (bool_type_book != 0 && bool_type_book != 1)
    {
    	 cout << "Выберите вид литературы:" << endl <<"0- Техническая" << endl << "1- Художественная " << endl;
    	 cout << ">>>";
		stream >> bool_type_book;
		if (!cin || (bool_type_book != 0 && bool_type_book != 1))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибочный ввод" << endl;
		}
    }

    if (!bool_type_book)
    {
        cout << "Введите отрасль: ";
		stream >> t_book.tech_book.industry;

		t_book.tech_book.Russian = -1;
		while (t_book.tech_book.Russian != 0 && t_book.tech_book.Russian != 1)
		{
			cout << "Выберите тип  произведения:" << endl << "0- отечественная" << endl << "1- переводная" << endl;
			cout << ">>>";
			stream >> t_book.tech_book.Russian;
			if (!cin || (t_book.tech_book.Russian != 0 && t_book.tech_book.Russian != 1))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибочный ввод" << endl;
			}
		}


		t_book.tech_book.publ_date = 0;
		while (t_book.tech_book.publ_date <=0)
		{
			cout << "Введите год издания: ";
			stream >> t_book.tech_book.publ_date;
			if (!cin || t_book.tech_book.publ_date <= 0)
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибочный ввод" << endl;
			}
		}
    }
    else
    {
    	cout << "Введите тип произведения: \n";
    	stream >> t_book.fict_book.genre;
    }

}








//void delet()
//{

//}


void delet(ifstream &stream, book_t *array)
{
    int slot = -1;
    //int i = 0, j = 0;

    cout << "Введите номер записи для удаления: ";
    while (slot < 0)
    {
    	cout << "Введите количество страниц: ";
    	stream >> slot;
    	if (!cin || slot < 0)
		{
    		cin.clear();
    		while (cin.get() != '\n');
    		cout << "Ошибочный ввод" << endl;
    	}
    }
    int j = 0;
    if (slot >= 1 && slot <= 200)
    {
        for (int i = 0; i < 200; ++i, array++)
        {
            if (array->author_name[0])
            {
                j++;
            }
            if (j == slot)
            {
                break;
            }
        }
        array->author_name = '\0';
    }
    else
    {
    	cout << "Такой записи не существует" << endl;
        //printf("Такой записи не существует\n");
    }
    cout << endl;
    //printf("\n");
}

bool book_t::search(int year, char *ind)
{
    if (bool_type_book)
        return false;
    //if (!t_book.tech_book.language_Russian)
    //    return false;

    if (strcmp(t_book.tech_book.industry, ind))
    {
    	return false;
    }
    //if (strcmp(t_book.tech_book.industry, ind) != 0)
    //    return false;

    if (t_book.tech_book.publ_date > year)
        return false;

    return true;


}

/*
void Book::create_record() {


    cout << "Введите автора: ";
    //cin >>author_name;
    author_name = "";
    getline(std::cin, author_name);


    book_title = "";
    cout << "Введите название: ";
    //cin >>book_title;
    getline(std::cin, book_title);


    cout << "Введите издательство: ";
    //>publisher;
    publisher = "";
    getline(std::cin, publisher);
    //cin >>publisher;

    string tmp;
    cout << "Введите количество страниц: ";
    pages = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> pages && pages > 0)
            break;
        cout << "Ошибочный ввод" << endl;
    }

    cout << "Выберите вид литературы: \n0- Техническая, \n1- Художественная \n";
    int x = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1))
            break;
        cout << "Ошибочный ввод" << endl;
    }


    book_t = type_book(x);

    switch (x) {
        case 0:
            book_record.tech.create_technical_book();
            break;
        case 1:
            book_record.art.create_art_book();
            break;
    }

}

void art_book::create_art_book() {

    cout << "Выберите тип  произведения: \n0- роман, \n1- пьеса, \n2- стихи\n";
    int x = -1;
    string tmp;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1 || x == 2))
            break;
        cout << "Ошибочный ввод" << endl;
    }
    art = kind_art(x);

}

void technical_book::create_technical_book() {

    cout << "Введите отрасль: \n";

    cin.getline(industry, sizeof industry);
    if (strlen(industry) > LEN_STRING) {
        cout << "Превышено количество символов!\n";
    }

    string tmp;
    cout << "Выберите тип  произведения: \n0- отечественная, \n1- переводная\n";
    int x = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1))
            break;
        cout << "Ошибочный ввод\n";
    }

    locate = kind_localization(x);
    cout << "Введите год издания\n";
    year = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> year && (year > 0 && year < 2017))
            break;
        cout << "Ошибочный ввод\n";
    }

}

void art_book::show() {

    cout << "Тип  произведения: ";
    switch (art) {
        case novels:
            cout << "роман" << endl;
            break;
        case plays:
            cout << "пьеса" << endl;
            break;
        case poems:
            cout << "стихи" << endl;
            break;
    }
}

void technical_book::show() {

    cout << "Отрасль: " << industry << endl;

    cout << "Тип  произведения: ";
    switch (locate) {
        case patriotic:
            cout << "отечественная" << endl;
            break;
        case translated:
            cout << "переводная" << endl;
            break;
    }

    cout << "Год издания: " << year << endl;

}

//Вывести список всей переводной лит-ры по указанной отрасли с годом издания не позднее указанного.

bool Book::search(int year, char *ind) {
    if (book_t != technical)
        return false;
    if (book_record.tech.locate != translated)
        return false;

    if (strcmp(book_record.tech.industry, ind) != 0)
        return false;

    if (book_record.tech.year > year)
        return false;

    return true;


}
*/
