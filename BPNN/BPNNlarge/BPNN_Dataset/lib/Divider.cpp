#include<fstream>
#include<iostream>
#include<string>
using namespace std;
#include"Divider.h"

void Divider(const char*filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Cannot open " << filename << endl;
		return;
	}
	ofstream fout_train, fout_validation;
	fout_train.open("train.csv");
	fout_validation.open("validation.csv");
	if (!fout_train.is_open()) {
		cout << "Cannot open train.csv\n";
		return;
	}
	if (!fout_validation.is_open()) {
		cout << "Cannot open validation.csv\n";
		return;
	}
	string str;
	int counter = 0;
	while (fin >> str) {
		if (counter > 4) {
			fout_validation << str << endl;
			counter = 0;
		}
		else {
			fout_train << str << endl;
			counter++;
		}
	}
}