#include <iostream>
#include <string>
#include <chrono>
#include <vector>

#include "binarytree.h"

/*
 * Лабораторная работа номер 6.
 * Удаление повторяющихся букв из строки.
 * Построить двоичное дерево поиска из букв вводимой строки.
Вывести его на экран в виде дерева.
 * Выделить цветом все буквы, встречающиеся более одного раза.
Удалить из дерева эти буквы.
 * Вывести оставшиеся элементы дерева при постфиксном его обходе.
 * Сравнить время удаления повторяющихся букв из дерева и из строки.
*/


unsigned long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void removeEqualitiesFromString(string& input)
{
    for (int i = 0; i < input.size(); i++)
    {
        vector<int> positions;
        positions.push_back(i);
        for (int j = i + 1; j < input.size(); j++)
            if (input[i] == input[j])
                positions.push_back(j);
        if (positions.size() != 1)
        {
            for (int j = 0; j < positions.size(); j++)
                for (int k = positions[j] - j; k < input.size() - 1; k++)
                    input[k] = input[k + 1];
            input = input.substr(0, input.size() - positions.size());
            i--;
        }
    }
}

int main(void)
{
    BinaryTree<char> tree;
    string input = "";
    vector<int> a;
    a.push_back(0);

    // Ввели строку.
    cout << "Введите строку\n";
    while (input == "")
    {
        getline(cin, input);
        if (input == "")
            cout << "Строка не должна быть пустой\n";
    }
    // Создали дерево.
    for (int i = 0; i  < input.size(); i++)
        tree.addNode(input[i]);

    // Постфиксный обход дерева.
    vector<char> v = tree.LRCVector();
    std::cout << "\nЭлементы дерева при постфиксном обходе: \n";
    if (v.size() == 0)
        std::cout << "<Ни одного элемента>";

    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";

    // Сравнение памяти.
    std::cout << "Память, затраченная на представление строки в виде дерева\n";
    std::cout << tree.memory() << " Байт\n\n";
    std::cout << "Память, затраченная на хранение строки\n";
    std::cout << input.size() << " Байт\n\n";

    // Вывод дерева.
    tree.visualizeColorRepeating();

    unsigned long tb, te, t;
    // Обработка дерева(удаление повторяющихся узлов).
    tb = tick();
    tree.removeDublicates();
    te = tick();
    tree.visualize(false, "graph2.gr", "graph2.png");

    // Постфиксный обход дерева.
    v = tree.LRCVector();
    std::cout << "\nОставшиеся после удаления повторяющихся элементы дерева при постфиксном обходе: \n";
    if (v.size() == 0)
        std::cout << "<Ни одного элемента>";

    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";

    // Сравнение времени.
    t = te - tb;
    std::cout << "\nВремя удаления повторяющихся узлов (ДЕРЕВО  ): " << t << " тик\n";

    tb = tick();
    removeEqualitiesFromString(input);
    te = tick();
    t = te - tb;
    std::cout << "\nВремя удаления повторяющихся узлов (СТАНДАРТ): " << t << " тик\n";


    // Дополнительные действия с деревом.
    char c, m = '1';
    int k = 3;
    while (m != '0')
    {
        std::cout << "Для добавления символа, введите 1. Для удаления - 2. Для выхода из программы - 0.\n";
        std::cin >> m;
        if (m == '1')
        {
            std::cout << "Можете добавить любой символ. Введите его:\n";
            std::cin >> c;
            tree.addNode(c);
            tree.visualize(false, string("graph") + to_string(k) + string(".gr"), string("graph") + to_string(k) + string(".png"));
        }
        if (m == '2')
        {
            std::cout << "Можете удалить любой символ. Введите его:\n";
            std::cin >> c;
            tree.remove(c);
            tree.visualize(false, string("graph") + to_string(k) + string(".gr"), string("graph") + to_string(k) + string(".png"));
        }
        k++;
    }
    return 0;
}
