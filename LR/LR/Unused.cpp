#include "Tuple.h"
using namespace std;
#define test

//	insert data to set named voca	and		emotionbar;
void train(string fname){
	char c;
	
	Attrnum = 0;
	int lines=0;
	bool nowweatthefirstline=true;
	fstream ftry(fname, ios::in);
	while((c=ftry.get()) != EOF){
		if(c == ','&&nowweatthefirstline==true){
			Attrnum++;
		}else if(c == '\n'){
			lines++;
			nowweatthefirstline = false;
		}
	}lines++;
	printf("[Unused]/train:num of attributes=%d\n", Attrnum);
	printf("[Unused]/train:samplelines=%d\n", lines);
	
	fstream f(fname, ios::in);
	for(int l=0; l<lines; l++){
		vector<double> xv; 
		for(int i=0; i<Attrnum; i++){
			double xi;	f >> xi;
			char c;		f >> c;
			if(c != ','||c == '\n'){
				cout << "c=" << c <<"|"<< endl;
				printf("[Unused]:You have changed the format of the file.\n");
				system("pause");
			}
			xv.push_back(xi);
		}
		short label;	f >> label;
		
		Tuple tp;
		tp.Setx_(xv);
		tp.label = label;
		Tuplebase.push_back(tp);
	}
	printf("[Unused]:Information extracting done.\n");
}

void valid(string fname){
	char c;
	
	Attrnum = 0;
	int lines=0;
	bool nowweatthefirstline=true;
	fstream ftry(fname, ios::in);
	while((c=ftry.get()) != EOF){
		if(c == ','&&nowweatthefirstline==true){
			Attrnum++;
		}else if(c == '\n'){
			lines++;
			nowweatthefirstline = false;
		}
	}lines++;
	printf("[Unused]/valid:num of attributes=%d\n", Attrnum);
	printf("[Unused]/valid:samplelines=%d\n", lines);
	
	fstream f(fname, ios::in);
	for(int l=0; l<lines; l++){
		vector<double> xv; 
		for(int i=0; i<Attrnum; i++){
			double xi;	f >> xi;
			char c;		f >> c;
			if(c != ','||c == '\n'){
				printf("[Unused]/valid:You have changed the format of the file.\n");
				system("pause");
			}
			xv.push_back(xi);
		}
		#ifndef test
		short label;	f >> label;
//		cout << label << endl;
		#endif
		#ifdef test
		string label;	f >> label;
//		cout << label << endl;
		#endif
		
		Tuple tp;
		tp.Setx_(xv);
		#ifndef test
		tp.label = label;
		#endif
		Validbase.push_back(tp);
	}
}
