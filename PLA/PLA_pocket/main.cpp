#include <iostream>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	printf("[train]:Analyzing train data...\n");
	printf("[train]:How many lines in the file:");
	int line; 	cin >> line;
	train("train.csv", line);
	printf("[train]:Analyzing train set done.\n");
	printf("[train]:Initialize weight expansion...\n");
	vector<double> w;
	for(int i=0; i<65; i++){
		w.push_back(1);
	}
	printf("[train]:Fixing the weight expansion...\n");
	int train_shoot = 0;
	int pocket_shoot = 0;
	vector<double> w_reg = w;
	
	int it=0;
	printf("Please set your iterator times:"); 
	cin >> it; 
//	while(train_shoot < 3280){
	for(int i=0; i<it; i++){
		train_shoot = 0;
		for(int i=0; i<Tuplebase.size(); i++){
			Tuple crt_tp = Tuplebase[i];
			bool shot=crt_tp.multiv(w_reg, true);
			if(shot){
				train_shoot++;
			}
		}
		if(train_shoot > pocket_shoot){
			cout << i <<"time\n"; 
			cout << "train_shoot:" << train_shoot << endl;
			printf("all size:");	cout << Tuplebase.size() << endl;
			pocket_shoot = train_shoot;
			w = w_reg;
		}
	}
	printf("\n\nfinal:\n");
	cout << "train_shoot:" << pocket_shoot << endl;
	printf("all size:");	cout << Tuplebase.size() << endl;
	printf("[train]:Fixed.\n\n");

//	collect valid sentences;
string file_name="val.csv";
#define set
	#ifndef set
	
	
	#endif
//	calculate every valid percent;
	#ifdef set
	
	printf("[valid]:Analyzing validation set...\n");
	printf("[valid]:How many rows:");
	int rows;	cin >> rows;
	valid(file_name, rows);
	printf("\n[valid]:Got sentences.\n");
	
	int shoot = 0;
	for(int i=0; i<Validbase.size(); i++){
		Tuple crt_tp = Validbase[i];
		bool shot = crt_tp.multiv(w, false);
		if(shot){
			shoot++;
		}
	}
	
	printf("[valid]:Datas stepping into files.\n");
	fstream fout("15352015_caogj_PLA.csv", ios::out);
	for(int i=0; i<output.size(); i++){
		fout << output[i] << endl;
	}
	printf("[valid]:validation set done.\n");
	
	printf("shoot %d.\tall %d.\n", shoot, Validbase.size());
	double Radio = 100*(double)shoot/Validbase.size();
	printf("Radio:%lf%\n", Radio);
	double Accuracy = (double)(Tp+Tn)/(Tp+Tn+Fp+Fn);
	double Recall = (double)Tp/(Tp+Tn);
	double Precision = (double)Tp/(Tp+Fp);
	double F1 = (2*Precision*Recall)/(Precision + Recall);
	printf("Accuracy=%lf\n", Accuracy);
	printf("Recall=%lf\n", Recall);
	printf("Precision=%lf\n", Precision);
	printf("F1=%lf\n", F1);

	#endif
	return 0;
}
