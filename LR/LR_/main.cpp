#include <iostream>
#include "Tuple.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	printf("[main]:Analyzing train data...\n");
	train("train.csv");
	printf("[main]:Analyzing done.\n");
	printf("[main]:Initialize weight expansion...\n");
	vector<double> w;
	for(int i=0; i<Attrnum; i++){
		w.push_back(0);
	}
	printf("[main]:Initialization done.\n");
	printf("[main]:Fixing the weight expansion...\n");
	int train_shoot = 0;
	int pocket_shoot = 0;
	vector<double> w_reg = w;
	double w0=0;
	
	for(int i=0; i<1; i++){
		train_shoot = 0;
		for(int i=0; i<Tuplebase.size(); i++){
			Tuple crt_tp = Tuplebase[i];
			bool shot=crt_tp.Jury(w0, w, w_reg, true);
			if(shot){
				train_shoot++;
			}
		}
		w = w_reg;
	}
	printf("[main]:Fixing done.\n");
	
	printf("\n\nw=_      _\n");
	cout << " |" << setw(8) << w0 << "|" << endl;
	for(int wpin=0; wpin<w.size(); wpin++){
		cout << " |" << setw(8) << w[wpin] << "|" << endl;
	}cout << " |_      _|\n\n\n";
	
//	collect valid sentences;
string file_name="valid.csv";
#define set
	#ifndef set
	#endif
//	calculate every valid percent;
	#ifdef set
	
	printf("[main]:Analyzing validation set...\n");
	valid(file_name);
	printf("[main]:Analyzing done.\n");
	
	printf("[main]:Calculating shoot count...\n");
	int shoot = 0;
	for(int i=0; i<Validbase.size(); i++){
		Tuple crt_tp = Validbase[i];
		bool shot = crt_tp.Jury(w0, w, w, false);
		if(shot){
			shoot++;
		}
	}
	printf("[main]:Calculating done.\n");
	
//	printf("[main]:shoot=%d.\tall=%d.\n", shoot, Validbase.size());
//	double Radio = 100*(double)shoot/Validbase.size();
//	printf("[main]:Radio:%lf%\n", Radio);

	#endif
	return 0;
}
