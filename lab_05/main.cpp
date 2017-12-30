#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <stdlib.h>

#include "MatrixRare.h"
#include "Matrix.h"

#define myRand (1 + (rand() % (int) (5 - 1 + 1)))
#define myRand100 (1 + (rand() % (int) (100 - 1 + 1)))
#define OK 0

using namespace std;

/*
 * Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
 * * вектор A содержит значения ненулевых элементов;
 * * вектор IA содержит номера строк для элементов вектора A;
 * * связный список JA, в элементе Nk которого находится номер компонент
в A и IA, с которых начинается описание столбца Nk матрицы A.

 * * Смоделировать операцию сложения двух матриц, хранящихся в этой форме,
с получением результата в той же форме.
 * * Произвести операцию сложения, применяя стандартный алгоритм работы
с матрицами.
 * * Сравнить время выполнения операций и объем памяти при использовании
этих 2-х алгоритмов при различном проценте заполнения матриц.
*/

unsigned long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void handleException(runtime_error e)
{
    cout << e.what() << endl;
    exit(EXIT_FAILURE);
}

void input(string s, int &value);
void mode(int &mode_tmp, int num);
void auto_input_matrix(int str, int stolb, vector<vector<int>> &m);
void manual_input_matrix(int str, int stolb, vector<vector<int>> &m);
void print_stream_matrix(Matrix &matrixA, MatrixRare &matrixRareA,
Matrix &matrixB, MatrixRare &matrixRareB, Matrix &matrixSum, MatrixRare &matrixRareSum);
vector<vector<int>> create_random_map(int stolb, int str, int zero_percent);
void printDoubleVector(vector<vector<int>> vect);
MatrixRare print_time_RareMatrix(MatrixRare matrixRareA, MatrixRare matrixRareB);
Matrix print_time_Matrix(Matrix matrixA, Matrix matrixB);

int main(void)
{
    cout << "ПРОГРАММА" << endl << "СЛОЖЕНИЕ МАТРИЦ" << endl << endl;
    srand(time(NULL));
//******************************************************************************
    int str = -1;
    int stolb = -1;
    int mode_tmp = -1;
    input("строк", str);
    input("столбцов", stolb);
    mode(mode_tmp, 1);
    vector<vector<int>> a;
    if (mode_tmp == 1)
    {
       auto_input_matrix(str, stolb, a);
    }
    else
    {
        manual_input_matrix(str, stolb, a);
    }
    MatrixRare matrixRareA;
    matrixRareA.create(a);
    Matrix matrixA;
    matrixA.create(a);
//******************************************************************************
    mode_tmp = -1;
    mode(mode_tmp, 2);
    vector<vector<int>> b;
    if (mode_tmp == 1)
    {
        auto_input_matrix(str, stolb, b);
    }
    else
    {
        manual_input_matrix(str, stolb, b);
    }
    MatrixRare matrixRareB;
    matrixRareB.create(b);
    Matrix matrixB;
    matrixB.create(b);
//******************************************************************************
    MatrixRare matrixRareSum = print_time_RareMatrix(matrixRareA, matrixRareB);
    Matrix matrixSum = print_time_Matrix(matrixA, matrixB);
    print_stream_matrix(matrixA, matrixRareA, matrixB, matrixRareB, matrixSum, matrixRareSum);
    return OK;
}

void input(string s, int &value)
{
    while (value == -1)
    {
        cout << "Введите количество "<< s << " матриц: " << endl;
        cin >> value;
        if (value == -1 || value <= 0)
        {
            cout << "Неправильный ввод, попробуйте снова" << endl;
            value = -1;
            cin.clear();
            cin.ignore(512, '\n');
        }
    }
}

void mode(int &mode_tmp, int num)
{
    cout << "Выберите режим ввода значений " << num;
    cout << " матрицы: авто(1)/ручной(2)" << endl;
    while (mode_tmp == -1)
    {
        cin >> mode_tmp;
        if (!(mode_tmp == 1 || mode_tmp == 2))
        {
            cout << "Неправильный ввод, попробуйте снова" << endl;
            mode_tmp = -1;
            cin.clear();
            cin.ignore(512, '\n');
        }
    }
    if (mode_tmp == 1)
        cout << "Выбран автоматический режим" << endl;
    if (mode_tmp == 2)
        cout << "Выбран ручной режим" << endl;
}

void auto_input_matrix(int str, int stolb, vector<vector<int>> &m)
{
    int percent = -1;
    while (percent == -1)
    {
        cout << "Введите процент нулей в массивах: " << endl;
        cin >> percent;
        if (percent == -1 || percent < 0 || percent > 100)
        {
            cout << "Неправильный ввод, попробуйте снова" << endl;
            percent = -1;
        }
    }
    m = create_random_map(stolb, str, percent);
}

void manual_input_matrix(int str, int stolb, vector<vector<int>> &m)
{
    m.clear();
    for (int i = 0; i < str; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < stolb; j++)
        {
            tmp.push_back(0);
        }
        m.push_back(tmp);
    }
    cout << "Чтобы закончить ввод напишите отрицательное значение номера строки";
    cout << endl;
    int d = 0,e = 0,c = 0;
    while (true)
    {
        cout << "Введите номер строки, стобца и значение через пробел" << endl;
        cin >> d;
        if (d == -1)
            break;
        cin >> e;
        if (e == -1)
            break;
        cin >> c;
        m[d][e] = c;
    }
}

void print_stream_matrix(Matrix &matrixA, MatrixRare &matrixRareA, Matrix &matrixB, MatrixRare &matrixRareB, Matrix &matrixSum, MatrixRare &matrixRareSum)
{
    int inptmp = -1;
    while (inptmp != 0)
    {
        cout << "Введите 0 для выхода из программы" << endl;
        cout << "Введите 1 для просмотра ПЕРВОЙ матрицы в стандартном представлении" << endl;
        cout << "Введите 2 для просмотра ПЕРВОЙ матрицы в разреженном представлении" << endl;
        cout << "Введите 3 для просмотра ВТОРОЙ матрицы в стандартном представлении" << endl;
        cout << "Введите 4 для просмотра ВТОРОЙ матрицы в разреженном представлении" << endl;
        cout << "Введите 5 для просмотра МАТРИЦЫ-СУММЫ  в стандартном представлении" << endl;
        cout << "Введите 6 для просмотра МАТРИЦЫ-СУММЫ  в разреженном представлении" << endl;
        cin >> inptmp;
        if (inptmp == 0)
            break;
        switch (inptmp)
        {
            case 1:
                matrixA.print();
                break;
            case 2:
                matrixRareA.printRare();
                break;
            case 3:
                matrixB.print();
                break;
            case 4:
                matrixRareB.printRare();
                break;
            case 5:
                matrixSum.print();
                break;
            case 6:
                matrixRareSum.printRare();
                break;
            default:
                cout << "Неизвестная команда\n";
                cin.clear();
                cin.ignore(512, '\n');
        }
        cout << endl << endl;
    }
}

vector<vector<int>> create_random_map(int stolb, int str, int zero_percent)
{
    vector<vector<int>> ans;
    int tmprand = 0;
    int zero = 0;
    for (int i = 0; i < str; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < stolb; j++)
        {
            tmprand = myRand;
            zero = myRand100;
            if (zero < zero_percent)
                tmprand = 0;
            tmp.push_back(tmprand);
        }
        ans.push_back(tmp);
    }
    return ans;
}

void printDoubleVector(vector<vector<int>> vect)
{
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[0].size(); j++)
        {
            cout << vect[i][j] << " ";
        }
        cout << endl;
    }
}

MatrixRare print_time_RareMatrix(MatrixRare matrixRareA, MatrixRare matrixRareB)
{
    unsigned long tb, te, t;
    tb = tick();
    MatrixRare matrixRareSum = matrixRareA + matrixRareB;
    te = tick();
    t = te - tb;
    cout << "\n\nСложение матриц...";
    cout << "\nВремя сложения в разреженном представлении: " << t << " тик";
    cout << endl << "Размер ПЕРВОЙ матрцы в разреженном представлении: ";
    cout << matrixRareA.getMemUsage() << endl;
    cout << "Размер ВТОРОЙ матрцы в разреженном представлении: ";
    cout << matrixRareB.getMemUsage() << endl;
    cout << "Размер МАТРИЦЫ-СУММЫ в разреженном представлении: ";
    cout << matrixRareSum.getMemUsage() << endl;
    return matrixRareSum;
}

Matrix print_time_Matrix(Matrix matrixA, Matrix matrixB)
{
    unsigned long tb, te, t;
    cout << endl;
    tb = tick();
    Matrix matrixSum = matrixA + matrixB;
    te = tick();
    t = te - tb;
    cout << "Время сложения в обычном представлении:     " << t << " тик";
    cout << endl << "Размер ПЕРВОЙ матрцы в обычном представлении:     ";
    cout << matrixA.getMemUsage() << endl;
    cout << "Размер ВТОРОЙ матрцы в обычном представлении:     ";
    cout << matrixB.getMemUsage() << endl;
    cout << "Размер МАТРИЦЫ-СУММЫ в обычном представлении:     ";
    cout << matrixSum.getMemUsage() << endl;
    return matrixSum;
}
