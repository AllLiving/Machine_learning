#include <iostream>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	printf("[train]:Analyzing train data...\n");
	train("train_set.csv");
	printf("[train]:Updating train data...\n");
	for(int i=0; i<Tuplebase.size(); i++){
		Tuplebase[i].Updatebaserow();
	}
	printf("[train]:Analyzing train set done.\n");

//	collect valid sentences;
string file_name="validation_set.csv";
#define set
	#ifndef set
	string s_tuple;
//	s_tuple = "more sleep healthier with gtwr children";
//	s_tuple = "hands on doomsday clock move forward";
	s_tuple = "england opt for bopara over loye";
//	s_tuple = "rig threat cargo ship towed ashore";
	Tuple tp;
	tp.Register(s_tuple);
	tp.visit_vocaset();
	tp.taste();
	tp.visit_emotionbar();
	#endif
//	calculate every valid percent;
	#ifdef set
	printf("[valid]:Analyzing validation set...\n");
	valid(file_name);
	printf("[valid]:Got sentences.\n");
	for(int i=0; i<Validbase.size(); i++){
		Tuple tp;
		tp.Register(Validbase[i]);
		tp.taste();
//		tp.visit_vocaset();
//		tp.visit_emotionbar();
//		system("pause");
	}
	printf("[valid]:Got datas for outputing.\n");
	
	fstream fout("15352015_NB_regression.csv", ios::out);
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
