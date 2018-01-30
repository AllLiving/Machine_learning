#include <iostream>
#include <bits/stdc++.h>
#include "Tuple.h"
#include "assess.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//	need a global vector<string> named wordbase;
//	so that we can summary all sentences, but not labels yet;
vector<string> Catch(string fname){
	fstream f(fname, ios::in);
	char c;
	string stmp;
	bool read = false;
	while((c=f.get()) != EOF){
		if(c == ','){
			read = false;
			if(stmp != ""){
				wordbase.push_back(stmp);
			}
			stmp = "";
		}
		else if(c == '\n')	read = true;
		if(read&&c != '\n'){
			stmp += c;
		}
	}
	return wordbase;
}

int main(int argc, char** argv) {
	printf("Analizing train set data...\n");
	fstream f("train_set.csv", ios::in);
//	rule out the head marks;
	printf("[Tuple]:Cleaning head marks.\n");
	char c;
	while((c=f.get()) != '\n');
//	a prepare section for; 
	string s_tuple;
	while((c=f.get()) != EOF){
		if(c == '\n'){
			Tuple tp;
			tp.Dismantle(s_tuple, true);
			Tuplebase.push_back(tp);
			s_tuple = "";
		}else{
			s_tuple += c;
		}
	}
	Tuple tmp;
	tmp.Dismantle(s_tuple, true);
	Tuplebase.push_back(tmp);
	printf("[Tuple]:Information extracting done.\n");
	
	for(int i=0; i<Tuplebase.size(); i++){
		Tuplebase[i].Updaterow();
	}
	printf("[Tuple]:Initialized tuples done.\n");
	printf("Analyze train set done.\n");
/*
we've get vocabulary base/tuples/labels/calculated rows of onehot-matrix
*/
#define set
	#ifndef set
	#define kkk 3
	Tuple tp;
	s_tuple = "martian life could have evaded detection by viking landers";//surprise;
	tp.Register(s_tuple);
	cout << "label:" << classify(tp, kkk) << endl;
	#endif
	#ifdef set
	printf("[main]:reading validation set data...\n");
	string fname = "test_set.csv";
	Catch(fname);
	printf("[main]:reading finished.\n");
	printf("[Tuple]:Classifying %d sentences...\n", wordbase.size());
//	deal with every sentences;
	for(int i=0; i<wordbase.size(); i++){
		Tuple tp;
		s_tuple = wordbase[i];
		tp.Register(s_tuple); 
		classify(tp, 15);//15
	}
	printf("[Tuple]:Classifying tuples done.\n");
	
	printf("[output]:writing into a file...\n");
	fstream fout("15352015_caogj_classification.csv", ios::out);
	fout << "id" << ',' << "label" << endl;
	for(int i=0; i<Forout_label.size(); i++){
		fout << i+1 << ',' << Forout_label[i] << endl;
	}
	printf("[output]:writing finished.\n");
	
	printf("[assess]assessing...\n");
	vector<string> fout_vec;
	vector<string> valid_vec;
	fout_vec = Read_label("fout.csv");
	valid_vec = Read_label(fname);
	printf("[assess]assessing done.\n");
	
	printf("\n\nConsequence:\n");
	cout << 100*Ratio(fout_vec, valid_vec) << '%' << endl;
	#endif
	return 0;
}
