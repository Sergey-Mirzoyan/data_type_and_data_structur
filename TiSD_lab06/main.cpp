#include <iostream>
#include "BinaryTree.h"

#include <string>
#include <chrono>
#include <vector>


void removeEqualitiesFromString(string& input) {
    for (int i = 0; i < input.size(); i++) {
        vector<int> positions;
        positions.push_back(i);
        for (int j = i + 1; j < input.size(); j++) {
            if (input[i] == input[j]) {
                positions.push_back(j);
            }
        }
        if (positions.size() != 1) {
            for (int j = 0; j < positions.size(); j++) {
                for (int k = positions[j] - j; k < input.size() - 1; k++) {
                    input[k] = input[k + 1];
                }
            }
            input = input.substr(0, input.size() - positions.size());
            i--;
        }
    }
}

int main() {
    BinaryTree<char> tree;
    string input = "";
    vector<int> a;
    a.push_back(0);
    cout << "Лабораторная работа номер 6. Удаление повторяющихся букв из строки.\n\n";
    cout << "Построить двоичное дерево поиска из букв вводимой строки. Вывести его на экран в виде дерева.\n"
            "Выделить цветом все буквы, встречающиеся более одного раза. Удалить из дерева эти буквы.\n"
            "Вывести оставшиеся элементы дерева при постфиксном его обходе.\n"
            "Сравнить время удаления повторяющихся букв из дерева и из строки.\n\n";
    cout << "Введите строку\n";
    while (input == "") {
        getline(cin, input);
        if (input == "")
            cout << "Строка не должна быть пустой\n";
    }
    for (int i = 0; i  < input.size(); i++) {
        tree.addNode(input[i]);
    }

    vector<char> v = tree.LRCVector();
    std::cout << "\nЭлементы дерева при постфиксном обходе: \n";
    if (v.size() == 0) {
        std::cout << "<Ни одного элемента>";
    }
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "Память, затраченная на представление строки в виде дерева\n";
    std::cout << tree.memory() << " Байт\n\n";
    std::cout << "Память, затраченная на хранение строки\n";
    std::cout << input.size() << " Байт\n\n";
    tree.visualizeColorRepeating();
    auto start = std::chrono::high_resolution_clock::now();
    tree.removeDublicates();
    auto finish = std::chrono::high_resolution_clock::now();
    tree.visualize(false, "graph2.gr", "graph2.png");

    v = tree.LRCVector();
    std::cout << "\nОставшиеся после удаления повторяющихся элементы дерева при постфиксном обходе: \n";
    if (v.size() == 0) {
        std::cout << "<Ни одного элемента>";
    }
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    std::cout << "\nВремя удаления повторяющихся узлов (ДЕРЕВО  ): " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << " наносекунд\n";

    start = std::chrono::high_resolution_clock::now();
    removeEqualitiesFromString(input);
    finish = std::chrono::high_resolution_clock::now();
    std::cout << "\nВремя удаления повторяющихся узлов (СТАНДАРТ): " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << " наносекунд\n";


    char c, m = '1';
    int k = 3;
    while (m != 'q') {
        std::cout << "Для добавления символа, введите 1. Для удаления - 2. Для выхода из программы - q.\n";
        std::cin >> m;
        if (m == '1') {
            std::cout << "Можете добавить любой символ. Введите его:\n";
            std::cin >> c;
            tree.addNode(c);
            tree.visualize(false, string("graph") + to_string(k) + string(".gr"), string("graph") + to_string(k) + string(".png"));
        }
        if (m == '2') {
            std::cout << "Можете удалить любой символ. Введите его:\n";
            std::cin >> c;
            tree.remove(c);
            tree.visualize(false, string("graph") + to_string(k) + string(".gr"), string("graph") + to_string(k) + string(".png"));
        }
        k++;
    }
    return 0;
}
