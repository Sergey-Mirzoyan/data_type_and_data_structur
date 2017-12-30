#include <vector>
#include <iostream>

using namespace std;

struct MatrixRare
{
    void create(vector<vector<int>> vect);
    MatrixRare operator+(const MatrixRare& other);
    int get(int stolb, int str) const;
    void print(void);
    vector<int> A;
    vector<int> IA;
    vector<int> JA;
    unsigned long stolb = 0;
    unsigned long str = 0;

    unsigned long getMemUsage(void);
    void printRare(void);
};
/*
 * Создание разреженной матрицы по стандартной.
 * this- получаемая матрица.
 * vect- стандартная матрица.
*/
void MatrixRare::create(vector<vector<int>> vect)
{
    stolb = vect[0].size();
    if (stolb <= 0)
        throw "Bad MatrixRare size";
    str = vect.size();
    if (str <= 0)
        throw "Bad MatrixRare size";
    int now = 0;
    bool ja_added = false;
    for (int i = 0; i < str; i++)
    {
        if (vect[i].size() != stolb)
            throw "Bad MatrixRare size";
        ja_added = false;
        for (int j = 0; j < stolb; j++)
        {
            now = vect[i][j];
            if (now != 0)
            {
                A.push_back(now);
                IA.push_back(j);
                if (!ja_added)
                {
                    ja_added = true;
                    JA.push_back(IA.size() - 1);
                }
            }
        }
        if (!ja_added)
            JA.push_back(-1);
    }

}

/*
 * Сумма двух матриц A- this и B- other
 * ans- Матрица суммы A и B.
*/
MatrixRare MatrixRare::operator+(const MatrixRare &other)
{
    if (stolb != other.stolb || str != other.str)
        throw "Cannot add MatrixRarees of different sizes";
    MatrixRare ans = MatrixRare();
    ans.stolb = stolb;
    ans.str = str;

    int jaind = 0;
    bool ja_added = false;
    vector<int> tmp(stolb);
    for (int i = 0; i < str; i++)
    {
        if (JA[i] == -1 && other.JA[i] == -1)
            continue;
        // обнуление вспомогательного вектора.
        for (int j = 0; j < stolb; j++)
            tmp[j] = 0;

        if (JA[i] != -1)
        {
            unsigned long end = A.size();
            //нахождение не нулевой строки в матрице A.
            int tmp_jaind = i + 1;
            while (tmp_jaind < str)
            {
                if (JA[tmp_jaind] != -1)
                {
                    end = JA[tmp_jaind];
                    break;
                }
                tmp_jaind++;
            }
            // заполнение вспомогательного вектора.
            jaind = JA[i];
            while (jaind != end)
            {
                tmp[IA[jaind]] += A[jaind];
                jaind++;
            }
        }

        if (other.JA[i] != -1)
        {
            unsigned long end = other.A.size();
            //нахождение не нулевой строки в матрице B.
            int tmp_jaind = i + 1;
            while (tmp_jaind < other.str)
            {
                if (other.JA[tmp_jaind] != -1)
                {
                    end = other.JA[tmp_jaind];
                    break;
                }
                tmp_jaind++;
            }
            // увеличение вспомогательного вектора.
            jaind = other.JA[i];
            while (jaind != end)
            {
                tmp[other.IA[jaind]] += other.A[jaind];
                jaind++;
            }
        }
        // заполнение суммы матриц.
        ja_added = false;
        for (int j = 0; j < tmp.size(); j++)
        {
            if (tmp[j] != 0)
            {
                ans.A.push_back(tmp[j]);
                ans.IA.push_back(j);
                // если элемент первый раз встречается в строке.
                if (!ja_added)
                {
                    ja_added = true;
                    ans.JA.push_back(ans.IA.size() - 1);
                }
            }
        }
        // если элемент не первый раз встречается в строке.
        if (!ja_added)
            ans.JA.push_back(-1);
    }
    return ans;
}

int MatrixRare::get(int sstr, int sstolb) const
{
    int jaind = JA[sstr];

    if (jaind == -1)
        return 0;

    unsigned long end = A.size();

    int tmp_jaind = sstr + 1;
    while (tmp_jaind < str)
    {
        if (JA[tmp_jaind] != -1)
        {
            end = JA[tmp_jaind];
            break;
        }
        tmp_jaind++;
    }

    jaind = JA[sstr];
    while (jaind < end)
    {
        if (IA[jaind] == sstolb)
            return A[jaind];
        jaind++;
    }
    return 0;
}

void MatrixRare::print(void)
{
    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < stolb; j++)
            cout << get(i,j) << " ";
        cout << endl;
    }
}

void MatrixRare::printRare(void)
{
    cout << " A:";
    for (int i = 0; i < A.size(); i++)
        cout << " " << A[i];
    cout << "\nIA:";
    for (int i = 0; i < IA.size(); i++)
        cout << " " << IA[i];
    cout << "\nJA:";
    for (int i = 0; i < JA.size(); i++)
        cout << " " << JA[i];
    cout << "\n";
}

unsigned long MatrixRare::getMemUsage(void)
{
    return (sizeof(this) + sizeof(int) * (A.size() + IA.size() + JA.size()));
}
