#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

#include"Reader.h"

//之前Lab文件读取的函数
//将文件逗号转换为空格 返回每行的元素数
static int transform(const char*);

static int transform(const char* t) {
	int ans = 0;
	ofstream fout;
	ifstream fin;
	fin.open(t);
	fout.open("transform.tmp");
	if (fin.is_open() && fout.is_open()) {
		char reading;
		bool first = 1;
		while (fin.good() && (reading = fin.get()) != -1) {
			if (reading == ',') {
				fout << ' ';
				if (first)ans++;
			}
			else if (first && reading == '\n') {
				//ans++;//used before lab, this lab is valid
				fout << reading;
				first = 0;
			}
			else fout << reading;
		}
	}
	else {
		cout << "Transform cannot open file!\n";
		system("pause");
	}
	fout.close();
	fin.close();
	return ans;
}
Reader::Reader(const char*filename) {
	vector<int>temp;
	//for reading
	int this_flag;
	int this_scalar;
	int this_column = 0;
	int this_row = -1;
	columns = transform(filename);
	string sst;

	ifstream fin;
	fin.open("transform.tmp");

	if (fin.is_open()) {
		while (fin.good() && fin >> sst) {
			if (this_column == 0) {
				data.push_back(temp);
				this_row++;
				stringstream ss(sst);
				ss >> this_scalar;
				data[this_row].push_back(this_scalar);
				this_column++;
			}
			else if (this_column < columns) {
				stringstream ss(sst);
				ss >> this_scalar;
				this_column++;
				data[this_row].push_back(this_scalar);
			}
			else {
				this_column = 0;
				stringstream ss(sst);
				ss >> this_flag;
				flag.push_back(this_flag);
			}
		}
	}
	else {
		cout << "Reader cannot open file!\n";
		system("pause");
	}
	rows = data.size();
}