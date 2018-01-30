#include <iostream>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 终止条件的设置
// 优化选择； 

int main(int argc, char** argv) {
	
	printf("[main]:Analyzing train data...\n");
	train("train.csv");
	printf("[main]:Analyzing done.\n");
	printf("[main]:Initialize weight expansion...\n");
	vector<double> w;
	for(int i=0; i<Attrnum; i++){
		w.push_back(i);
	}
	printf("[main]:Initialization done.\n");
	printf("[main]:Fixing the weight expansion...\n");
	int train_shoot = 0;
	int pocket_shoot = 0;
	vector<double> w_reg = w;
	
	for(int i=0; i<60; i++){
		int train_shoot = 0;
		for(int i=0; i<Tuplebase.size(); i++){
			Tuple crt_tp = Tuplebase[i];
			bool shot=crt_tp.Jury(w_reg, true);
			if(shot){
				train_shoot++;
			}
		}
//		if(train_shoot > pocket_shoot){
//			cout << i <<"time\n"; 
//			cout << "train_shoot:" << train_shoot << endl;
//			printf("all size:");	cout << Tuplebase.size() << endl;
//			pocket_shoot = train_shoot;
//		}
//		if(w == w_reg){
//			printf("iterator end.\n");
//			system("pause");
//		}
		w = w_reg;
	}
	printf("[main]:Fixing done.\n");
	
	printf("\n\nfinal:\n");
	cout << "train_shoot:" << pocket_shoot << endl;
	printf("all size:");	cout << Tuplebase.size() << endl;
	printf("[main]:Fixed.\n\n");

//	collect valid sentences;
string file_name="test.csv";
#define set
	#ifndef set
	#endif
//	calculate every valid percent;
	#ifdef set
	
	printf("output size=%d\n", output.size());
	output.clear();
	printf("[main]:Analyzing validation set...\n");
	valid(file_name);
	printf("[main]:Analyzing done.\n");
	
	printf("[main]:Calculating shoot count...\n");
	int shoot = 0;
	for(int i=0; i<Validbase.size(); i++){
		Tuple crt_tp = Validbase[i];
		bool shot = crt_tp.Jury(w, false);
		if(shot){
			shoot++;
		}
	}
	printf("[main]:Calculating done.\n");
	
	printf("[valid]:Datas stepping into files.\n");
	fstream fout("15352015_caogj_LR.txt", ios::out);
	printf("output size=%d\n", output.size());
	for(int i=0; i<output.size(); i++){
		fout << output[i] << endl;
	}
	printf("[valid]:validation set done.\n");
	
	printf("[main]:shoot=%d.\tall=%d.\n", shoot, Validbase.size());
	double Radio = 100*(double)shoot/Validbase.size();
	printf("[main]:Radio:%lf%\n", Radio);

	#endif
	return 0;
}
