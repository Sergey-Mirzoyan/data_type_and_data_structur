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

bool book_t::search(int year, char *ind)
{
    if (bool_type_book)
    {
        return false;
    }

    if (strcmp(t_book.tech_book.industry, ind))
    {
    	return false;
    }

    if (t_book.tech_book.publ_date > year)
    {
        return false;
    }

    return true;
}
