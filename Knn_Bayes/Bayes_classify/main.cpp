#include <iostream>
#include <bits/stdc++.h>
#include "Tuple.h"
#include "Emlabel.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("[train]:Analyzing train data...\n");
	train("train_set.csv");
	for(int i=0; i<Tuplebase.size(); i++){
		Tuplebase[i].telescope();
		Tuplebase[i].Updaterow();
		allabel.push_back(Tuplebase[i].label);
		vector<string>::iterator it = 
			find(labelbase.begin(), labelbase.end(), Tuplebase[i].label);
		if(it == labelbase.end())
			labelbase.push_back(Tuplebase[i].label);
	}
	printf("[train]:Analyzing train set done.\n");

//	collect valid sentences;
string file_name="test_set.csv";
#define set
	#ifndef set
	string s_tuple;
	s_tuple = "marijuana ease hiv nerve pain study says";
	Tuple tp;
	tp.Register(s_tuple);
	tp.telescope();
	tp.taste();
	#endif
//	calculate every valid percent;
	#ifdef set
	printf("[valid]:Analyzing validation set...\n");
	valid(file_name);
	printf("[valid]:Got sentences.\n");
	vector<string> output;
	for(int i=0; i<Validbase.size(); i++){
		Tuple tp;
		tp.Register(Validbase[i]);
		tp.telescope(); 
		tp.taste();
		output.push_back(tp.label);
	}
	printf("[valid]:Got datas for outputing.\n");
	
	printf("[valid]:Datas stepping into files.\n");
	fstream fout("15352015_Bayes_classification.csv", ios::out);
	fout << "id" << ',' << "label" << endl;
	for(int i=0; i<output.size(); i++){
		fout << i+1 << ',' << output[i] << endl;
	}
	printf("[valid]:validation set done.\n");
	
//	printf("[assess]assessing...\n");
//	vector<string> fout_vec;
//	vector<string> valid_vec;
//	fout_vec = Read_label("fout.csv");
//	valid_vec = Read_label(file_name);
//	printf("fout_vec size=%d\n", fout_vec.size());
//	printf("valid_vec size=%d\n", valid_vec.size());
//	system("pause");
//	printf("[assess]assessing done.\n");
//	
//	printf("\n\nConsequence:\n");
//	cout << 100*Ratio(fout_vec, valid_vec) << '%' << endl;
	#endif
	
	return 0;
}
