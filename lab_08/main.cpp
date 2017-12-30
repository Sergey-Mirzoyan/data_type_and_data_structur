#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>

#include <stdio.h>

#include "GraphShower.h"

using namespace std;
const int MAXN = 100;
int n, g[MAXN][MAXN], g2[MAXN][MAXN];;
int best_cost = 1000000000;
vector<int> best_cut;

//fname - абсолютный или относительный путь к фаилу
void init_graph(std::string fname)
{
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
		{
			g[i][j] = 0;
			g2[i][j] = 0;
		}

	std::ifstream in(fname, std::ifstream::in);
	int init, fin;
	in >> n;
	while (in.good())
	{
		in >> init >> fin;
		g[fin - 1][init - 1] = 1;
		g[init - 1][fin - 1] = 1;

		g2[fin - 1][init - 1] = 1;
		g2[init - 1][fin - 1] = 1;
	}
	in.close();
}

void mincut(void)
{
    vector<int> v[MAXN];
    for (int i = 0; i < n; ++i)
        v[i].assign(1, i);

    int w[MAXN];
    bool exist[MAXN], in_a[MAXN];
    memset(exist, true, sizeof exist);

    for (int ph = 0; ph < n - 1; ++ph)
    {
        memset(in_a, false, sizeof in_a);
        memset(w, 0, sizeof w);

        for (int it = 0, prev; it < n - ph; ++it)
        {
            int sel = -1;
            for (int i = 0; i < n; ++i)
                if (exist[i] && !in_a[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            if (it == n - ph - 1)
            {
                if (w[sel] < best_cost)
                    best_cost = w[sel], best_cut = v[sel];
                    //printf("%d %d %d\n", best_cost, sel, v[sel][0]);
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < n; ++i)
                    g[prev][i] = g[i][prev] += g[sel][i];
                //printf("%d %d\n", prev, sel);
                exist[sel] = false;
            }
            else
            {
                in_a[sel] = true;
                for (int i = 0; i < n; ++i)
                    w[i] += g[sel][i];
                prev = sel;
            }
        }
    }
}

void loader()
{
	char a;
	std::string fname;
    string patch="./";

	cout<<"Выберите один из графов"<<endl;
	cout<<"0. Три треугольника"<<endl;
	cout<<"1. Два треугольника"<<endl;
	cout<<"2. Два квадрата"<<endl;
	cout<<"3. \"Кубок\"" <<endl;
	cout<<"4. Пятиугольник"<<endl;
	cout<<"5. Квадрат с диагональю"<<endl;
	cin>>a;
	switch (a)
	{
		case '0': fname = patch+"data.txt";
			break;
		case '1': fname = patch+"data1.txt";
			break;
		case '2': fname = patch+"data2.txt";
			break;
		case '3': fname = patch+"data3.txt";
			break;
		case '4': fname = patch+"data4.txt";
			break;
		case '5': fname = patch+"data5.txt";
			break;
		default: cout<<"Error. Loaded first graph"<<endl;
	}
	init_graph(fname);
}


void  hand_input()
{
	for (int i = 0; i < MAXN; ++i)
		for (int j = 0; j < MAXN; ++j)
		{
			g[i][j] = 0;
			g2[i][j] = 0;
		}


	int init, fin;
	cout << "Введите кол-во вершин: ";
	while (!(scanf("%d", &n)) || (n <= 0) || (n >= MAXN))
	{
		cout << "Error" << endl;
	}
	cout << "Введите кол-во ребер: ";
	int count;
	cin>>count;
	cout << "Введите ребра: ";
	while (count>0)
	{
		cin>> init >> fin;
		if(init<0 ||fin<0)
		{
			break;
		}
		if(init>n-1 ||fin>n-1)
		{
			cout<<"Не верное ребро. Попробуйте еще раз."<<endl;
		}
		count--;
		g[fin - 1][init - 1] = 1;
		g[init - 1][fin - 1] = 1;
		g2[fin - 1][init - 1] = 1;
		g2[init - 1][fin - 1] = 1;
	}

}
int main()
{


    char a;

	cout << endl;
	cout << "**************************************************************" << endl;
	cout << "Выберите одно из следующих действий:" << endl;
	cout << "0: Загрузить граф из файла" << endl;
	cout << "1: Задать граф" << endl;
	cout << "2: Закончить работу" << endl;
	cin >> a;
	switch (a)
	{
		case '0':
			loader();
			break;
		case '1':
			hand_input();
			break;
		case '2':
			return 0;
		default:
			return 0;
	}

	//Показыватели графов
	int remove_counter = 0;
    GraphShower gsh1 = {"f1.data", "Old graph", "pic1.png"};//"/tmp/f1.data", "Old graph", "/tmp/pic1.png");
    GraphShower gsh2 = {"f2.data", "New graph", "pic2.png"};
    for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (g2[i][j] == 1)
				gsh1.printer(i + 1, j + 1);
		}
		gsh1.print(i + 1);
	}

    gsh1.show();


	mincut();

    for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (g2[i][j] == 1)
			{
				bool flag1 = false;
				bool flag2 = false;

				for (int k = 0; k < best_cut.size(); ++k)
				{
					if (i == best_cut[k])
						flag1 = true;
					if (j == best_cut[k])
						flag2 = true;
				}

				if (flag1 != flag2)
				{
					g2[i][j] = 0;
					cout << "Ребро для удаления " << i + 1 << "-" << j + 1 << endl;
					remove_counter++;
				}
			}

            if (g2[i][j] == 1)
            {
                gsh2.printer(i + 1, j + 1);
            }


		}
        gsh2.print(i + 1);
	}

	cout << "Ребер удалено: " << remove_counter << endl;
	gsh2.show();
	best_cut.empty();

}
