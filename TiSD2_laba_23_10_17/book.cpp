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
    cout << "�����: " << author_name << endl;
    cout << "��������: " << name_book << endl;
    cout << "������������: " << publ_office << endl;
    cout << "���-�� �������: " << pages << endl;

    cout << "��� ����������: ";
    switch (bool_type_book)
    {
        case 0:
            cout << "�����������" << endl;

			cout << "�������: " << t_book.tech_book.industry << endl;

			cout << "���  ������������: ";
			switch (t_book.tech_book.Russian)
			{
				case 0:
					cout << "�������������" << endl;
					break;
				case 1:
					cout << "����������" << endl;
					break;
			}

			cout << "��� �������: " << t_book.tech_book.publ_date << endl;
            break;
        case 1:
            cout << "��������������" << endl;
			cout << "���  ������������: " << t_book.fict_book.genre << endl;
            break;
    }
}

void book_t::create_book(istream& stream)
{
	author_name = "";
    cout << "������� ������: ";
    stream >> author_name;


    name_book = "";
    cout << "������� ��������: ";
    stream >>name_book;


    publ_office = "";
    cout << "������� ������������: ";
    stream >> publ_office;


    pages = 0;
    while (pages <= 0)
    {
    	cout << "������� ���������� �������: ";
    	stream >> pages;
    	if (!cin || pages <= 0)
		{
    		cin.clear();
    		while (cin.get() != '\n');
    		cout << "��������� ����" << endl;
    	}
    }

    bool_type_book = -1;
    while (bool_type_book != 0 && bool_type_book != 1)
    {
    	 cout << "�������� ��� ����������:" << endl <<"0- �����������" << endl << "1- �������������� " << endl;
    	 cout << ">>>";
		stream >> bool_type_book;
		if (!cin || (bool_type_book != 0 && bool_type_book != 1))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "��������� ����" << endl;
		}
    }

    if (!bool_type_book)
    {
        cout << "������� �������: ";
		stream >> t_book.tech_book.industry;

		t_book.tech_book.Russian = -1;
		while (t_book.tech_book.Russian != 0 && t_book.tech_book.Russian != 1)
		{
			cout << "�������� ���  ������������:" << endl << "0- �������������" << endl << "1- ����������" << endl;
			cout << ">>>";
			stream >> t_book.tech_book.Russian;
			if (!cin || (t_book.tech_book.Russian != 0 && t_book.tech_book.Russian != 1))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "��������� ����" << endl;
			}
		}


		t_book.tech_book.publ_date = 0;
		while (t_book.tech_book.publ_date <=0)
		{
			cout << "������� ��� �������: ";
			stream >> t_book.tech_book.publ_date;
			if (!cin || t_book.tech_book.publ_date <= 0)
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "��������� ����" << endl;
			}
		}
    }
    else
    {
    	cout << "������� ��� ������������: \n";
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

    cout << "������� ����� ������ ��� ��������: ";
    while (slot < 0)
    {
    	cout << "������� ���������� �������: ";
    	stream >> slot;
    	if (!cin || slot < 0)
		{
    		cin.clear();
    		while (cin.get() != '\n');
    		cout << "��������� ����" << endl;
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
    	cout << "����� ������ �� ����������" << endl;
        //printf("����� ������ �� ����������\n");
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


    cout << "������� ������: ";
    //cin >>author_name;
    author_name = "";
    getline(std::cin, author_name);


    book_title = "";
    cout << "������� ��������: ";
    //cin >>book_title;
    getline(std::cin, book_title);


    cout << "������� ������������: ";
    //>publisher;
    publisher = "";
    getline(std::cin, publisher);
    //cin >>publisher;

    string tmp;
    cout << "������� ���������� �������: ";
    pages = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> pages && pages > 0)
            break;
        cout << "��������� ����" << endl;
    }

    cout << "�������� ��� ����������: \n0- �����������, \n1- �������������� \n";
    int x = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1))
            break;
        cout << "��������� ����" << endl;
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

    cout << "�������� ���  ������������: \n0- �����, \n1- �����, \n2- �����\n";
    int x = -1;
    string tmp;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1 || x == 2))
            break;
        cout << "��������� ����" << endl;
    }
    art = kind_art(x);

}

void technical_book::create_technical_book() {

    cout << "������� �������: \n";

    cin.getline(industry, sizeof industry);
    if (strlen(industry) > LEN_STRING) {
        cout << "��������� ���������� ��������!\n";
    }

    string tmp;
    cout << "�������� ���  ������������: \n0- �������������, \n1- ����������\n";
    int x = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> x && (x == 0 || x == 1))
            break;
        cout << "��������� ����\n";
    }

    locate = kind_localization(x);
    cout << "������� ��� �������\n";
    year = -1;
    while (true) {
        getline(cin, tmp);
        stringstream myStream(tmp);
        if (myStream >> year && (year > 0 && year < 2017))
            break;
        cout << "��������� ����\n";
    }

}

void art_book::show() {

    cout << "���  ������������: ";
    switch (art) {
        case novels:
            cout << "�����" << endl;
            break;
        case plays:
            cout << "�����" << endl;
            break;
        case poems:
            cout << "�����" << endl;
            break;
    }
}

void technical_book::show() {

    cout << "�������: " << industry << endl;

    cout << "���  ������������: ";
    switch (locate) {
        case patriotic:
            cout << "�������������" << endl;
            break;
        case translated:
            cout << "����������" << endl;
            break;
    }

    cout << "��� �������: " << year << endl;

}

//������� ������ ���� ���������� ���-�� �� ��������� ������� � ����� ������� �� ������� ����������.

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
