#include <iostream>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <malloc.h>

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
    return book1.pages > book2.pages;
}

bool isLess(Table_key book1, Table_key book2)
{
    return book1.pages > book2.pages;

}

bool isLess(Table_key *book1, Table_key *book2)
{
    return &(book1->pages) > &(book2->pages);

}

bool isLess(book_t *book1, book_t book2)
{
    return book1->pages > book2.pages;
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
	char str[LEN_STRING];
	int x;
	cout << "Введите год издания: ";
	cin >> year;

    for (int i = 0; i < n; ++i)
    {
        if (arr[i].search(year, industry) == true) {
            arr[i].show();
        }

    }
}
/*
int Remove(book_t *arr, int *k) {
    int n = *k;
    int z;
    cout << "Введите индекс удаляемой записи от 0 до " << n - 1;
    cin >> z;
    if (z < 0 || z >= n) {
        cout << "Выход из диапазона" << endl;
        return 1;
    }

    for (int i = z; i < n; i++) {
        memcpy(&arr[i], &arr[i + 1], sizeof(Book));
    }

    // arr[n].~Book();
    //arr[n] = Book();

    cout << "Элемент был удален удален" << endl;
    n--;
    *k = n;
    return 0;
}
*/

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
		//mySort(keys,0,n,isLess);
		quick_sort(keys, keys + n - 1);
		t2 = tick();
		sum_key += t2 - t1;
		//cout << sum_key;
    }

    unsigned long long sum_not_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка таблицы
		t3 = tick();//clock();
		//mySort(arr,0,n,isLess);
		quick_sort(arr, arr + n - 1);
		t4 = tick();
		//cout << t2 << ' ' << t1;
		sum_not_key += t4 - t3;
		//cout << sum_key;
    }

    //cout<< sum_key << ' ' << sum_not_key << endl;
    cout << "Время работы сортировки по ключам (быстрой сортировкой): " << sum_key/5 << " тик" << endl;
    cout << "Время работы сортировки таблицы: (быстрой сортировкой): " << sum_not_key/5 << " тик" << endl;

    for (int i = 0; i < n; i++)
    {
        //keys[i] = Table_key(i, arr[i]);
        arr3[i] = arr[i];
    }

    sum_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка по ключам
		t1 = tick();
		mySort(keys, 0, n, isLess);
		//quick_sort(keys,keys+n-1);
		t2 = tick();
		sum_key += t2 - t1;
	}

    sum_not_key = 0;
    for (int i = 0; i < 5; ++i)
    {
		//Сортировка таблицы
		t3 = tick();
		mySort(arr3, 0, n, isLess);
		//quick_sort(arr,arr+n-1);
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
	unsigned long long sum_key_qsort = 0;
    for(int i = 0; i < 5; ++i)
	{
		t1 = tick();
		quick_sort(keys, keys + n - 1);
		t2 = tick();
		sum_key_qsort += t2 - t1;
	}


    for (int i = 0; i < 5; ++i)
    {
        cout << keys[i].id << " ";
        keys[i] = Table_key(i, arr[i]);
    }
    cout << endl;
	
	unsigned long long sum_key_bsort = 0;
	for (int i = 0; i < 5; ++i)
	{
		t3 = tick();
		mySort(keys, 0, n, isLess);
		t4 = tick();
		sum_key_bsort += t4 - t3;
	}

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        arr[keys[i].id].show();
        cout << endl;
    }
    cout << endl;

    cout << "Время работы быстрой сортировки: " << sum_key_qsort/5 << " тик" << endl;
    cout << "Время работы сортировки пузырьком: " << sum_key_bsort/5 << " тик" << endl;

}


void Key_sort(book_t *arr, int n, Table_key *keys)
{
    for (int i = 0; i < n; i++)
    {
        keys[i] = Table_key(i, arr[i]);
        cout << keys[i].id << " ";
    }
    cout << endl;
    //mySort(keys,0,n,isLess);
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

int main(void)
{

    book_t *arr2 = new book_t[MAX_RECORD];
    int count;

    //time_t t1, t2, t3, t4;
	
    ifstream fin;
    fin.open("database.txt");

    if (!fin.is_open())
    {
        cout << "Файл не может быть открыт!\n";
        return -1;
    }
    else
    {
    	char *tmp = new char[1024];
		fin >> tmp;
		count = atoi(tmp);
		readFromFile(fin, arr2, count);
    }

    book_t *arr = new book_t[MAX_RECORD];
    for (int i = 0; i < count; i++)
    {
        memcpy(&arr[i], &arr2[i], sizeof(book_t));
    }

    //n = n2;
    Table_key keys[MAX_RECORD];
    while (true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;

        cout << "0: Показать таблицу" << endl;
        cout << "1: Отсортировать по ключам (не меняя исходную)" << endl;
        cout << "2: Отсортировать таблицу" << endl;
        cout << "3: Добавить запись" << endl;
        cout << "4: Сравние времени сортировки таблицы и ключей" << endl;
        cout << "5: Сравнить эффективность сортировок (по ключам)" << endl;
        cout << "6: Поиск по году и отрасли" << endl;
        cout << "7: Выход" << endl;
        cout << ">>>";

/*
        {
            int flag = 0;
            char str[LEN_STRING];
            int x;
            do {
                flag = 0;
                //cin >> str;


                cin.getline(str, LEN_STRING, '\n');
                char **end = NULL;
                x = strtol(str, end, 10);
                if (x < 0 || x > 2017) {
                    cout << "Ошибочный ввод" << endl;
                    flag = 1;
                }
            } while (flag);

            a = x;
        }
*/
//cout << "4: Удалить запись" << endl;
        int a;
        cin >> a;
        int n = count;

        switch (a)
        {
            case 0:
            	cout << count << endl;//n << endl;
                for (int i = 0; i <= count; i++)
                {
                    cout << i << endl;
                    arr[i].show();
                    cout << endl;
                }


                break;
///////////////////////////////////////////////////////////////////////////
            case 1:
                Key_sort(arr, count, keys);
                break;
///////////////////////////////////////////////////////////////////////////
            case 2:
                //mySort(arr,0,n,isLess);
                quick_sort(arr, arr + count - 1);

                for (int i = 0; i < count; i++)
                {
                    arr[i].show();
                    cout << endl;
                }
                break;
///////////////////////////////////////////////////////////////////////////
            case 3:
                if (count >= MAX_RECORD - 1)
                {
                    cout << "Переполнение массива записей" << endl;
                    break;
                }
                arr[count].create_book(cin);
                ++count;
                break;
            //case 4:
            // 	delet(cin, arr);
            //    if (Remove(arr, &n) == 0) {
            //        for (int i = 0; i < n; i++) {
            //            cout << i << endl;
            //            arr[i].show();
            //            cout << endl;
            //        }
            //    }
            //    cin.clear();
            //    //cin.sync();
            //    cin.ignore(INT8_MAX, '\n');
            //
            //    break;
///////////////////////////////////////////////////////////////////////////
            case 4:
                Sort_to_time(arr, count, keys);
                break;
            case 5:
                DifSort(arr, count, keys);
                break;
            case 6:
                Search(arr, count);
                break;
            //case 8:
            //
            //    arr = (book_t *) malloc(sizeof(book_t) * MAX_RECORD);
            //
             //   for (int i = 0; i < count; i++)
              //  {
//
  //                  memcpy(&arr[i], &arr2[i], sizeof(book_t));
    //                //arr[i]=arr2[i];
      //          }
//
//
  //              arr[count - 1] = arr2[count - 1];
//
  //              for (int i = count; i < MAX_RECORD; i++)
    //            {
      //              arr[i] = book_t();
        //        }
//
  //              n = count;
//
  //              break;
//

            case 7:
                cout << "Выход" << endl;
                return 0;
            default:
                cout << "Ошибочный ввод" << endl;
                break;

        }
    }

}
