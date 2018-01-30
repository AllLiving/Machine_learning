#include <iostream>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	printf("[train]:Analyzing train data...\n");
//	printf("[train]:How many lines in the train file:");
//	int line; 	cin >> line;
	train("thur78train.csv", 8);
	printf("[train]:Analyzing train set done.\n");
	printf("[train]:Initialize weight expansion...\n");
	vector<double> w;
	for(int i=0; i<6; i++){
		w.push_back(1);
	}
	printf("[train]:Fixing the weight expansion...\n");
	
	int train_shoot = 0;
	for(int i=0; i<Tuplebase.size(); i++){
		Tuple crt_tp = Tuplebase[i];
		bool shot=crt_tp.multiv(w, true);
		if(shot){
			train_shoot++;
		}
	}
	cout << "train_shoot:" << train_shoot << endl;
	printf("all size:");	cout << Tuplebase.size() << endl;
	printf("[train]:Fixed.\n\n");

//	collect valid sentences;
	string file_name="thur78test.csv";
	
	printf("[valid]:Analyzing validation set...\n");
//	printf("[valid]:How many rows in the validation file:");
//	int rows;	cin >> rows;
	valid(file_name, 2);
	printf("\n[valid]:Got sentences.\n");
	
	int shoot = 0;
	for(int i=0; i<Validbase.size(); i++){
		Tuple crt_tp = Validbase[i];
		bool shot = crt_tp.multiv(w, false);
		if(shot){
			shoot++;
		}
	}
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

	return 0;
}
