#include <bits\stdc++.h>
#include "Sample.h"
#include <iostream>
using namespace std;

#define DEBUG
// sample a file, divide into several files
bool sample(const string filename) {
	char c;
	int lines = 0, Attrnum = 1;
	bool SizeFirstLine = true;
	fstream ftry(filename, ios::in);
	while ((c = ftry.get()) != EOF) {
		if (c == ','&&SizeFirstLine == true) {
			Attrnum++;
		}
		else if (c == '\n') {
			lines++;
			SizeFirstLine = false;
		}
	}
	printf("[Sample]:num of attributes=%d\n", Attrnum);
	printf("[Sample]:sample lines=%d\n", lines);

	fstream f(filename, ios::in);
	for (int l = 0; l<lines; l++) {
		for (int i = 0; i<Attrnum-1; i++) {
			double xi;	f >> xi;
#ifdef DEBUG
			cout << setw(10) << xi;
#endif // DEBUG

			char c = ',';
			f >> c;
#ifdef DEBUG
			cout << c;
#endif // DEBUG
			if (c != ',' || c == '\n') {
				printf("[Sample]:You have changed the format of the file.\n");
				system("pause");
			}
		}
		double label;
		f >> label;
#ifdef DEBUG
		cout << setw(10) << label << endl;
#endif // DEBUG
	}
	printf("[Sample]:Information extracting done.\n");
	return true;
}
