#include "Tuple.h"
using namespace std;
#define test

//	insert data to set named voca	and		emotionbar;


void train(string fname, int lines){
	fstream f(fname, ios::in);
	
	for(int i=0; i<lines; i++){
		vector<double> xv; 
		for(int i=0; i<6; i++){
			double xi;	f >> xi;
//			cout << xi << ' ';
			char c;		f >> c;
//			cout << c;
			if(c != ','||c == '\n'){
				printf("[train]:You have changed the format of the file.\n");
				system("pause");
			}
			xv.push_back(xi);
		}
		short label;	f >> label;
//		cout << label << endl;
		
		Tuple tp;
		tp.Setx_(xv);
		tp.label = label;
		Tuplebase.push_back(tp);
	}
	printf("[Tuple]:Information extracting done.\n");
}


void valid(string fname, int lines){
	fstream f(fname, ios::in);
	
//	char c;
//	while((c=f.get()) != EOF){
//		cout << c;
//	}
//	system("pause");
	
	for(int i=0; i<lines; i++){
		vector<double> xv; 
		for(int i=0; i<6; i++){
			double xi;		f >> xi;
			cout << xi << ' ';
			char c;			f >> c;
			cout << c;
			if(c != ','||c == '\n'){
				printf("\n[valid]:You have changed the format of the file.\n");
			} 
			xv.push_back(xi);
		}
		#ifndef test
		short label;	f >> label;
		#endif
		#ifdef test
		string label;	f >> label;
		cout << label << endl;
		system("pause");
		#endif 
		
		Tuple tp;
		tp.Setx_(xv);
		#ifndef test
		tp.label = label;
		#endif
		Validbase.push_back(tp);
	}
}
