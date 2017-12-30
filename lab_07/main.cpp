#include <iostream>
#include <chrono>

#include "library.h"
#include "AVL.cpp"
#include "BST.cpp"
#include "HashTableClose.cpp"
#include "HashTableOpen.cpp"

int compare_count;
void probel(int n);
unsigned int hash_function(Data<char> const & obj);
unsigned int hash_function(Data<int> const & obj);

/*
 * Задание (Вариант 1):
 * Построить хеш-таблицу по указанным данным.
 * Сравнить эффективность поиска в сбалансированном двоичном дереве,
в двоичном дереве поиска и в хеш-таблице (используя открытую и закрытую адресацию).
 * Вывести на экран деревья и хеш-таблицы.
 * Подсчитать среднее количество сравнений для поиска данных в указанных структурах.
 * Произвести реструктуризацию хеш-таблицы, если среднее количество сравнений больше указанного.
 * Оценить эффективность использования этих структур (по времени и памяти) для
поставленной задачи.
 * Оценить эффективность поиска в хеш-таблице при различном количестве коллизий
и при различных методах их разрешения.
*/

unsigned long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

//template <typename T>
vector<int> check_in_time;

template<typename T>
void from_file_to_struct(T *obj)
{
    ifstream inp;
    inp.open("data.txt");
    int data;
    while (inp >> data)
    {
        obj->Insert(Data<int>(data));
        check_in_time.push_back(int(data));
    }

    inp.close();
}

template<typename T>
void from_string_to_struct(string str, T *obj)
{
    for (int i = 0; i < str.size(); i++)
        if (isalpha(str[i]))
        {
            obj->Insert(Data<char>(str[i]));
            check_in_time.push_back(int(str[i]));
        }
}

template<typename Tp,typename T>
void work_with_tree(T *tree)
{
    char a;
    Tp data;
    while (true)
    {

        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "1: Отобразить дерево" << endl;
        cout << "2: Добавить число в дерево" << endl;
        cout << "3: Удалить число из дерева" << endl;
        cout << "4: Удалить все вхождения числа в дереве" << endl;
        cout << "5: Поиск числа" << endl;
        cout << "6: Закончить работу" << endl;
        cin >> a;
        switch (a)
        {
            case '1':
                show(tree);
                break;
            case '2':
                cout << "Введите число: " << endl;
                cin >> data;
                tree->Insert(Data<Tp>(data));
                check_in_time.push_back(int(data));
                break;
            case '3':
                cout << "Введите число: " << endl;
                cin >> data;
                if (tree->Remove(Data<Tp>(data)))
                    cout << "Число успешно удалено" << endl;
                else
                    cout << "Дерево не содержит числа" << endl;
                break;
            case '4':
                cout << "Введите число: " << endl;
                cin >> data;
                while (tree->Search(Data<Tp>(data)))
                    tree->Remove(Data<Tp>(data));
                cout << "Число успешно удалено" << endl;
                break;
            case '5':
                cout << "Введите число: " << endl;
                cin >> data;
                cout << (tree->Search(Data<Tp>(data)) ? "Число есть в дереве" : "Числа нет в дереве") << endl;
                break;
            case '6':
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }
}

template<typename Tp,typename T>
void work_with_table(T *table)
{
    char a;
    Tp data;
    while (true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "1: Отобразить таблицу" << endl;
        cout << "2: Добавить число в таблицу" << endl;
        cout << "3: Удалить число из таблицы" << endl;
        cout << "4: Удалить все вхождения числа в таблице" << endl;
        cout << "5: Поиск числа" << endl;
        cout << "6: Закончить работу" << endl;
        cin >> a;
        switch (a)
        {
            case '1':
                table->Show();
                break;
            case '2':
                cout << "Введите число: " << endl;
                cin >> data;
                table->Insert(Data<Tp>(data));
                check_in_time.push_back(int(data));
                break;
            case '3':
                cout << "Введите число: " << endl;
                cin >> data;
                if (table->Delete_element(Data<Tp>(data)))
                {
                    cout << "Число успешно удалено" << endl;
                }
                else
                {
                    cout << "Таблица не содержит числа" << endl;
                }
                break;
            case '4':
                cout << "Введите число: " << endl;
                cin >> data;
                while (table->Delete_element(Data<Tp>(data)));
                cout << "Число успешно удалено" << endl;
                break;
            case '5':
                cout << "Введите число: " << endl;
                cin >> data;
                cout << (table->Search(Data<Tp>(data)) ? "Число есть в таблице" : "Числа нет в таблице") << endl;
                break;
            case '6':
                return;
            default:
                cout << "Команда не найдена";
                break;
        }
    }

}

template<typename Tp,typename T>
bool find(char ch, T *obj)
{
    compare_count = 0;
    auto startN = tick();
    Data<Tp> tmp(ch);
    bool res = obj->Search(tmp);
    auto finishN = tick();
    cout << "Время работы(тик):   " << finishN - startN << endl;
    cout << "Кол-во сравнений:   " << compare_count << endl;
    cout << "Объем памяти(байт): " << obj->Memory() << endl;
    //TODO подсчет памяти
    return res;
}

template<typename Tp,typename T>
unsigned long find_all(char ch, T *obj)
{
    compare_count = 0;
    auto startN = tick();
    Data<Tp> tmp(ch);
    bool res = obj->Search(tmp);
    auto finishN = tick();
    return (finishN - startN);
}

template <typename Tp>
void check_time(BST<Data<Tp>> *binary_tree, AVL<Data<Tp>> *avl_tree, HashTableClose<Data<Tp>> *close_table, HashTableOpen<Data<Tp>> *open_table)
{
    auto res_b = 0;
    auto res_avl = 0;
    auto res_close = 0;
    auto res_open = 0;
    int count = 0;
    for (auto i : check_in_time)
    {
        count++;
        res_b += find_all<Tp>(i, binary_tree);
        res_avl += find_all<Tp>(i, avl_tree);
        res_close += find_all<Tp>(i, open_table);
        res_open += find_all<Tp>(i, close_table);
    }
    cout << "Среднее время поиска:" << endl;
    cout << "Бинарное дерево: " << res_b/count << endl;
    cout << "Avl дерево: " << res_avl/count << endl;
    cout << "Таблица с открытой адресацией: " << res_open/count << endl;
    cout << "Таблица с закрытой адресацией: " << res_close/count << endl;
}

template <typename  Tp>
void interface()
{
    char menu_index;
    Tp data;

    BST<Data<Tp>> *binary_tree = new BST<Data<Tp>>();
    AVL<Data<Tp>> *avl_tree = new AVL<Data<Tp>>();
    HashTableClose<Data<Tp>> *close_table = new HashTableClose<Data<Tp>>(4);
    HashTableOpen<Data<Tp>> *open_table = new HashTableOpen<Data<Tp>>(4);
    while (true)
    {
        cout << "**************************************************************" << endl;
        cout << "Выберите одно из следующих действий:" << endl;
        cout << "0: Загрузить данные из файла" << endl;
        cout << "1: Работа с деревом поиска" << endl;
        cout << "2: Работа с АВЛ деревом" << endl;
        cout << "3: Работа с хэш таблицей с открытой адресацией" << endl;
        cout << "4: Работа с хэш таблицей с закрытой адресацией" << endl;
        cout << "5: Сравнение времени поиска" << endl;
        cout << "6: Закончить работу" << endl;
        cin >> menu_index;
        switch (menu_index)
        {
            case '0':
                from_file_to_struct(binary_tree);
                from_file_to_struct(avl_tree);
                from_file_to_struct(close_table);
                from_file_to_struct(open_table);
                cout << "Элементы добавлены в структуры\n" << endl;
                break;
            case '1':
                work_with_tree<Tp>(binary_tree);
                break;
            case '2':
                work_with_tree<Tp>(avl_tree);
                break;
            case '3':
                work_with_table<Tp>(open_table);
                break;
            case '4':
                work_with_table<Tp>(close_table);
                break;
            case '5':
                //cout << "Введите число: " << endl;
                //cin >> data;
                check_time(binary_tree, avl_tree, close_table, open_table);
                break;
            case '6':
                return ;
            default:
                cout << "Команда не найдена"<<endl;
                break;
        }
    }
}

int main(void)
{
    interface<int>();
    return 0;
}

void probel(int n)
{
    for(int i = 0; i < n; i++)
        cout << " ";
}

unsigned int hash_function(Data<char> const & obj)
{
    return (unsigned int) (obj.value);
}

unsigned int hash_function(Data<int> const & obj)
{
    return (unsigned int) (obj.value);
}
