#include "Split.h"
#include <iostream>
#include <bits\stdc++.h>
using namespace std;


bool split(const string filename, const string file1, const string file2, const int interval) {
	/*fstream ftry(filename, ios::in);
	char c;
	int attrnum = 0;
	while ((c=ftry.get()) != EOF)
	{
		if (c == ','){	attrnum++;	}
		else if (c == '\n'){	break;	}
	}
	printf("[Split]: %d attributes exist.\n", attrnum);*/

	printf("[Split]:Begin split the file into two files.\n");
	char c;
	int line = 0;
	fstream fin(filename, ios::in);
	fstream ft1(file1, ios::out);
	fstream ft2(file2, ios::out);
	while ((c=fin.get()) != EOF)
	{
		if ((line%interval) == 0) {
			ft1 << c;
		}
		else
		{
			ft2 << c;
		}
		if (c == '\n')	line++;
	}
	printf("[Split]:Splitation done.\n");
	return true;
}
