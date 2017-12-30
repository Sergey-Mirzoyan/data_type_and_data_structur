//
// Created by alexey on 16.12.16.
//

#ifndef TISD8_GRAPHSHOWER_H
#define TISD8_GRAPHSHOWER_H

#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

class GraphShower
{
    ofstream out;
    string fname;
    string picname;


public:
	GraphShower(string filename, string graphname, string pic)
	{
		fname = filename;
		picname = pic;
		out.open(fname);
		out << "digraph G{\n";
        out << "labelloc=\"t\"\n";
        out << "label=\"";
        out << graphname;
        out << "\"\n";
	}

    void printer(int from, int to)
	{
        out << from << "->" << to << "[dir=both]" << endl;
	}

	void print(int from)
	{
        out << from << endl;
	}

	void show()
	{
        out << "}";
        out.close();

        string script1 = "dot -Tpng " + fname + " -o " + picname;
        system(script1.data());
	}
};

#endif //TISD8_GRAPHSHOWER_H
