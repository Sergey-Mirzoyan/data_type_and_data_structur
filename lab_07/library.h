#ifndef TISD7_LIBRARY_H_H
#define TISD7_LIBRARY_H_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define LEN_WORD 256
#define CONSOL_SIZE 128

using namespace std;

template <typename T>
void printer(ofstream out, int from, int to)
{
    out << from << "->" << to << "[dir=both]" << endl;
}

template <typename T>
void print_file(ofstream out, T from)//, T from)
{
    out << int(from) << endl;
}

extern int compare_count;
extern void probel(int n);

template <typename T>
void print(T *tmp, int deep, bool flag)
{
    if(tmp)
    {
        for (int i = 0; i < deep - 1; i++)
            cout << "|    ";
        if (deep >= 1)
            cout << "|----";
        cout << tmp->key << endl;
        flag = false;
        if(tmp->left || tmp->right)
            flag = true;
        print(tmp->left, deep + 1, flag);
        print(tmp->right, deep + 1, flag);
    }
    else if(flag)
    {
        for (int i = 0; i < deep - 1; i++)
            cout << "|    ";
        if (deep >= 1)
            cout << "|----";
        cout << "-----" << endl;
    }
}
template <typename T>
void show_as_tree(T* tree)
{
    print(tree->head, 0, true);
}
template <typename T>
void print_tree(T *h)
{
    queue<T *> A;
    A.push(h);
    T *tmp = NULL;
	int level = 0;
	int flag = 1;
    ofstream file_in;
    file_in.open("pic1.gr");
    file_in << "digraph G{\n";
    file_in << "labelloc=\"t\"\n";
    file_in << "label=\"";
    file_in << "PIC1";
    file_in << "\"\n";
    probel(5);
    while(!A.empty() && flag && level < 5) {
        flag = 0;
        int step = CONSOL_SIZE / pow(2, level + 1);
        //cout << step << endl;
        //int index = step;
        for(int i = 0; i < pow(2, level); i++) {
            tmp = A.front();
            A.pop();
            probel(step - 3);
            //index += 2 * step;
            if (tmp == NULL) {
                A.push(NULL);
                A.push(NULL);
                probel(6);
            }
            else
            {
                //cout << "[check]" << tmp->key << ' ' << tmp->left->key << ' ' << tmp->right->key << endl;
                if (tmp->right && tmp->left)
                {
                    //cout << "[check]" << tmp->key << ' ' << tmp->left->key << ' ' << tmp->right->key << endl;
                    file_in << tmp->key << "->" << tmp->left->key << "[dir=both]" << endl;
                    file_in << tmp->key << "->" << tmp->right->key << "[dir=both]" << endl;
                }
                else if(tmp->right)
                {
                    //cout << "[check]" << tmp->key << ' ' << tmp->right->key << endl;
                    file_in << tmp->key << "->" << tmp->right->key << "[dir=both]" << endl;
                }
                else if (tmp->left)
                {
                    //cout << "[check]" << tmp->key << ' ' << tmp->left->key << endl;
                    file_in << tmp->key << "->" << tmp->left->key << "[dir=both]" << endl;
                }
                else
                {
                    //cout << "[check]" << tmp->key << endl;
                    file_in << tmp->key << endl;
                }
                cout << tmp->key;
                probel(6 - tmp->key.print_width());
                A.push(tmp->left);
                A.push(tmp->right);
                flag = 1;
            }
            probel(step - 4);
            cout << " ";
        }
        cout << endl;
        cout << endl;
        level++;
    }
    file_in << "}";
    string script1 = "dot -Tpng pic1.gr -o ex1.png";
    system(script1.data());
}

template <typename T>
void show(T* tree)
{
	print_tree(tree->head);
}

template <typename T>
class Data {
public:
	T value;
	int count;
	Data(T tmp) {
		value = tmp;
		count = 1;
	}
	Data() {
		count = 0;
	}
    Data<T>(Data<T> const &obj)
    {
		//cout << "copy_data:" << obj << endl;
		value = obj.value;
		count = obj.count;
	}
    Data<T>& operator = (Data<T> const &obj)
    {
		//cout << "ko";
		if(this != &obj) {
			value = obj.value;
			count = obj.count;
		}
		return *this;
	}
    int print_width()
    {
		int res = 3;
		int copy = count;
        while(copy > 0)
        {
			res++;
			copy /= 10;
		}
		return res;
	}
    template <typename X>
    friend unsigned int hash_function(Data<X> const & obj);

	template <typename X>
	friend std::ostream & operator <<(std::ostream & os, Data<X> const & n);

    friend bool operator ==(Data const & a, Data const & b)
    {
		compare_count++;
		return a.value == b.value;
	}
    friend bool operator !=(Data const & a, Data const & b)
    {
        return !(a == b);
    }
    friend bool operator <(Data const & a, Data const & b)
    {
        compare_count++;
        return a.value < b.value;
    }
    friend bool operator >(Data const & a, Data const & b)
    {
        compare_count++;
        return a.value > b.value;
    }

    friend bool operator <=(Data const & a, Data const & b)
    {
        return !(a > b);
    }

    friend bool operator >=(Data const & a, Data const & b)
    {
        return !(a < b);
    }
};

template <typename T>
std::ostream & operator <<(std::ostream & os, Data<T> const & n)
{
    os << n.value ;//<< "(" << n.count << ")";
}

#endif //TISD7_LIBRARY_H_H
