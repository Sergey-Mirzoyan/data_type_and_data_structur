#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "Book.h"
#include "Table_key.h"

#define MAX_RECORD 200

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d) );

	return d;
}

using namespace std;

bool isLess(book_t book1, book_t book2)
{
    return book1.name_book > book2.name_book;
}

bool isLess(Table_key book1, Table_key book2)
{
    return book1.name_book > book2.name_book;

}

bool isLess(Table_key *book1, Table_key *book2)
{
    return &(book1->name_book) > &(book2->name_book);

}

bool isLess(book_t *book1, book_t book2)
{
    return book1->name_book > book2.name_book;
}

template<class T>
void mySort(T *arr, int l, int r, bool (*isLess)(T, T))
{
    for (int i = l; i < r; i++)
    {
        for (int j = i + 1; j < r; j++)
        {
            if (isLess(arr[i], arr[j]))
                swap(arr[i], arr[j]);

        }
    }
}

template<class T>
void quick_sort(T *begin, T *end)
{
    T *i = begin, *j = end, x = *(i + (j - i) / 2);

    do
    {
        while (isLess(x, *i)) i++;
        while (isLess(*j, x)) j--;

        if (i <= j)
        {
            if (isLess(*i, *j))
            {
                swap(*i, *j);
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < end)
    {
        quick_sort(i, end);
    }
    if (begin < j)
    {
        quick_sort(begin, j);
    }
}

void Search(book_t *arr, int n)
{
    char industry[1024];
	cout << "Введите отрасль: ";
    cin >> industry;

    int year;
	cout << "Введите год издания: ";
	cin >> year;

    for (int i = 0; i < n; ++i)
    {
        if (arr[i].search(year, industry) == true) {
            arr[i].show();
        }

    }
}

int delet(book_t *arr, int *k) {
    int n = *k;
    int z;
    cout << "Введите индекс удаляемой записи от 0 до " << n - 1;
    cin >> z;
    if (z < 0 || z >= n) {
        cout << "Выход из диапазона" << endl;
        return 1;
    }

    for (int i = z; i < n; i++)
    {
        memcpy(&arr[i], &arr[i + 1], sizeof(book_t));
    }

    cout << "Элемент был удален удален" << endl;
    n--;
    *k = n;
    return 0;
}

void Sort_to_time(book_t *arr, int n, Table_key *keys)
{
    unsigned long long t1, t2, t3, t4;
    book_t arr3[MAX_RECORD];
    for (int i = 0; i < n; i++)
    {
        keys[i] = Table_key(i, arr[i]);
        arr3[i] = arr[i];
    }

    unsigned long long sum_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка по ключам
		t1 = tick();
		quick_sort(keys, keys + n - 1);
		t2 = tick();
		sum_key += t2 - t1;
    }

    unsigned long long sum_not_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка таблицы
		t3 = tick();
		quick_sort(arr, arr + n - 1);
		t4 = tick();
		sum_not_key += t4 - t3;
    }

    cout << "Время работы сортировки по ключам (быстрой сортировкой): " << sum_key/5 << " тик" << endl;
    cout << "Время работы сортировки таблицы: (быстрой сортировкой): " << sum_not_key/5 << " тик" << endl;

    for (int i = 0; i < n; i++)
    {
        arr3[i] = arr[i];
    }

    sum_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка по ключам
		t1 = tick();
		mySort(keys, 0, n, isLess);
		t2 = tick();
		sum_key += t2 - t1;
	}

    sum_not_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка таблицы
		t3 = tick();
		mySort(arr3, 0, n, isLess);
		t4 = tick();
		sum_not_key += t4 - t3;
	}

    cout << "Время работы сортировки по ключам (Пузырек): " << sum_key/5 << " тик" << endl;
    cout << "Время работы сортировки таблицы: (Пузырек): " << sum_not_key/5 << " тик" << endl;

}

void DifSort(book_t *arr, int n, Table_key *keys)
{
    unsigned long long t1, t2, t3, t4;
    for (int i = 0; i < n; i++)
    {
        keys[i] = Table_key(i, arr[i]);
        cout << keys[i].id << " ";
    }
    cout << endl;

    int sum_key_1 = 0;
    for(int i = 0; i < 5; ++i)
    {
		t1 = tick();
		quick_sort(keys, keys + n - 1);
		t2 = tick();
		sum_key_1 += t2 - t1;
    }

    for (int i = 0; i < n; i++)
    {
        cout << keys[i].id << " ";
        keys[i] = Table_key(i, arr[i]);
    }
    cout << endl;

    int sum_key_2 = 0;
    for (int i = 0; i < 5; ++i)
    {
		t3 = tick();
		mySort(keys, 0, n, isLess);
		t4 = tick();
		sum_key_2 += t4 - t3;
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        arr[keys[i].id].show();
        cout << endl;
    }
    cout << endl;

    cout << "Время работы быстрой сортировки: " << sum_key_1/5 << " тик" << endl;
    cout << "Время работы сортировки пузырьком: " << sum_key_2/5 << " тик" << endl;

}

/*--------------------------------------------------------------------------*/
void Key_sort(book_t *arr, int n, Table_key *keys)
{
    for (int i = 0; i < n; i++)
    {
        keys[i] = Table_key(i, arr[i]);
        cout << keys[i].id << " ";
    }
    cout << endl;
    quick_sort(keys, keys + n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << keys[i].id << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        arr[keys[i].id].show();
        cout << endl;
    }
    cout << endl;
}

int write_to_file(book_t *arr, int count)
{
	cout << "Напишите название файла, куда будет производиться запись: ";
	char name_file[1024];
	cin >> name_file;
	FILE * file_2 = fopen(name_file, "w");
	if (!file_2)
	{
		return 1;
	}
	fprintf(file_2, "Кол-во элементов: %7d\n", count);
	fprintf(file_2, "Автор  Название  Издательство Кол-во страниц Тип литературы [Жанр/Индустрия] [Российская/Переводная] [Год публикации]\n");
	for (int i = 0; i < count; ++i, arr++)
	{
		fprintf(file_2, "%7s %10s %15s %5d " , arr->author_name.c_str(), arr->name_book.c_str(), arr->publ_office.c_str(), arr->pages);
		if (arr->bool_type_book)
		{
			fprintf(file_2, "    Художественная %15s\n", arr->t_book.fict_book.genre);
		}
		else
		{
			fprintf(file_2, "    Техническая %15s ", arr->t_book.tech_book.industry);
			if (arr->t_book.tech_book.Russian)
			{
				fprintf(file_2, "    Российская %15d\n", arr->t_book.tech_book.publ_date);
			}
			else
			{
				fprintf(file_2, "    Переводная %15d\n", arr->t_book.tech_book.publ_date);
			}
		}
	}
	fclose(file_2);
	return 0;
}

void Show(book_t *arr, int count)
{
	cout << count << endl;
	for (int i = 0; i < count; i++)
	{
		cout << i << endl;
		arr[i].show();
		cout << endl;
	}
}

int menu()
{
	for (int i = 0; i < 79; ++i)
	{
		cout << "-" ;
	}
	cout << endl;
	cout << "Выберите одно из следующих действий:" << endl;
	cout << "0: Выход" << endl;
	cout << "1: Показать таблицу" << endl;
	cout << "2: Отсортировать по ключам (не меняя исходную)" << endl;
	cout << "3: Отсортировать таблицу" << endl;
	cout << "4: Добавить запись" << endl;
	cout << "5: Удалить запись" << endl;
	cout << "6: Сравние времени сортировки таблицы и ключей" << endl;
	cout << "7: Сравнить эффективность сортировок (по ключам)" << endl;
	cout << "8: Поиск по году и отрасли" << endl;
	cout << "9: Запись массива в файл" << endl;
	cout << ">>>";

	int menu_p = 0;
	cin >> menu_p;
	return menu_p;
}

/*--------------------------------------------------------------------------*/
int main(void)
{
    ifstream file;
    file.open("database.txt");

    if (!file.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }
    book_t *arr = new book_t[MAX_RECORD];
	char tmp[1024] = "";
	file >> tmp;
	int count = atoi(tmp);
	readFromFile(file, arr, count);
	file.close();

    Table_key keys[MAX_RECORD];
    while (true)
    {
    	int menu_p = menu();
        switch (menu_p)
        {
/*--------------------------------------------------------------------------*/
            case 1:
            	Show(arr, count);
                break;
/*--------------------------------------------------------------------------*/
            case 2:
                Key_sort(arr, count, keys);
                break;
/*--------------------------------------------------------------------------*/
            case 3:
                quick_sort(arr, arr + count - 1);
                Show(arr, count);
                break;
/*--------------------------------------------------------------------------*/
            case 4:
                if (count >= MAX_RECORD - 1)
                {
                    cout << "Переполнение массива записей" << endl;
                    break;
                }
                arr[count].create_book(cin);
                ++count;
                break;
/*--------------------------------------------------------------------------*/
            case 5:
             	if(!delet(arr, &count) && count)
             	{
                    Show(arr, count);
                }
             	else if (!count)
             	{
             		cout << "Пустой массив" << endl;
             	}
             	else
             	{
             		cout << "Ошибка удаления";
             		delete[] arr;
             		return -1;
             	}
             	break;
/*--------------------------------------------------------------------------*/
            case 6:
                Sort_to_time(arr, count, keys);
                break;
/*--------------------------------------------------------------------------*/
            case 7:
                DifSort(arr, count, keys);
                break;
/*--------------------------------------------------------------------------*/
            case 8:
                Search(arr, count);
                break;
            case 9:
                if (write_to_file(arr, count))
                {
					cout << "Файл не может быть открыт";
					delete[] arr;
					return -1;
                }
                break;
/*--------------------------------------------------------------------------*/
            case 0:
                cout << "Выход" << endl;
                delete[] arr;
                return 0;
/*--------------------------------------------------------------------------*/
            default:
                cout << "Ошибочный ввод" << endl;
                break;
/*--------------------------------------------------------------------------*/
        }
    }
}
