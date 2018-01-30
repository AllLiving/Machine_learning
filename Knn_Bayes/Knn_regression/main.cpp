#include <iostream>
#include <bits/stdc++.h>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("[train]:Analyzing train data...\n");
	train("train_set.csv");
	for(int i=0; i<Tuplebase.size(); i++){
		Tuplebase[i].Updaterow();
	}
	printf("[train]:Analyzing train set done.\n");

//	collect valid sentences;
string file_name="test_set.csv";
#define set
	#ifndef set
	string s_tuple;
	s_tuple = "thousands line up to get late flu shots";//175/304/383/436/542/
	Tuple tp;
	tp.Register(s_tuple);
	tp.telescope();
	tp.taste(5);
	tp.brain.visit_feelbar();
	#endif
//	calculate every valid percent;
	#ifdef set
	printf("[valid]:Analyzing validation set...\n");
	valid(file_name);
	printf("[valid]:Got sentences.\n");
	for(int i=0; i<Validbase.size(); i++){
		Tuple tp;
		tp.Register(Validbase[i]);
		tp.taste(5);
		tp.brain.visit_feelbar();
	}
	printf("[valid]:Got datas for outputing.\n");
	
	fstream fout("15352015_KNN_regression.csv", ios::out);
	printf("[valid]:Datas stepping into files.\n");
	for(int i=0; i<output.size(); i++){
		if((i%6)==0 && i!=0){
			fout << endl;
		}
		fout << output[i] << ',';
	}
	printf("[valid]:validation set done.\n");
	#endif
	
	return 0;
}
