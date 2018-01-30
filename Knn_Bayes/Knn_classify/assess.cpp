#include <iostream>
#include <bits/stdc++.h>
#include "assess.h"
using namespace std;

vector<string> Read_label(string fname){
	fstream fin(fname, ios::in);
	char c;
	bool Is_label = false;
	vector<string> labelbase;
	while((c=fin.get()) != '\n');
	while((c=fin.get()) != EOF){
		if(c == ','||c == '\n')	Is_label = !Is_label;
		if(Is_label){
			string label;
			fin >> label;
//			cout << "label:" << label << endl;
			labelbase.push_back(label);
		}
	}
	return labelbase;
}

double Ratio(vector<string> va, vector<string> vb){
	if(va.size() != vb.size()){
		printf("va size=%d"); 	cout << va.size() << endl;
		printf("vb size=%d");	cout << vb.size() << endl;
		printf("[assess.cpp/Radio]va's size != vb's size.\n");
	}
	double size = va.size(), cnt = 0;
	for(int i=0; i<size; i++){
		if(va[i] == vb[i])	cnt++;
		else{
//			cout << "index=" << i << endl;
//			cout << "va:" << va[i] << endl;
//			cout << "vb:" << vb[i] << endl;
		}
	}
	printf("cnt=%lf\n", cnt);
	printf("size=%lf\n", size);
	return ((double)cnt/size);
}
