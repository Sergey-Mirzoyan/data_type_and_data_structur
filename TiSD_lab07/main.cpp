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

template<typename T>
void from_file_to_struct(T *obj)
{
    ifstream inp;
    inp.open("data.txt");
    int data;
    while (inp >> data)
        obj->Insert(Data<int>(data));

    inp.close();
}

template<typename T>
void from_string_to_struct(string str, T *obj)
{
    for (int i = 0; i < str.size(); i++)
        if (isalpha(str[i]))
            obj->Insert(Data<char>(str[i]));
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
                break;
            case '3':
                cout << "Введите число: " << endl;
                cin >> data;
                if (table->Delete_element(Data<Tp>(data)))
                {
                    cout << "Число успешно удалено" << endl;
                } else
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
    auto startN = std::chrono::high_resolution_clock::now();
    Data<Tp> tmp(ch);
    bool res = obj->Search(tmp);
    auto finishN = std::chrono::high_resolution_clock::now();
    cout << "Время работы(нс):   " << std::chrono::duration_cast<std::chrono::nanoseconds>(finishN-startN).count() << endl;
    cout << "Кол-во сравнений:   " << compare_count << endl;
    cout << "Объем памяти(байт): " << obj->Memory() << endl;
    //TODO подсчет памяти
    return res;
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
                cout << "Введите число: " << endl;
                cin >> data;
                cout << "Время поиска" << endl;
                cout << "\nБинарное дерево: \n";
                find<Tp>(data, binary_tree);
                cout << "\nAvl дерево: \n";
                find<Tp>(data, avl_tree);
                cout << "\nТаблица с открытой адресацией: \n";
                find<Tp>(data, open_table);
                cout << "\nТаблица с закрытой адресацией: \n";
                find<Tp>(data, close_table);
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
