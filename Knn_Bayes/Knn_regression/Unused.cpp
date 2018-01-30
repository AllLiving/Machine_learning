#include "Tuple.h"
using namespace std;

void train(string fname){
	fstream f(fname, ios::in);
	char c1, cpin;
	while((c1 = f.get()) != '\n');
	c1=f.get();
//	printf("[Tuple]:Cleaned head marks.\n");
	string s;
	while((cpin=f.get()) != EOF){
		if(cpin == ','){
			s += c1;
			
			Tuple tp;
//			cout << s << endl;
			tp.Collectvoc(s, true);//
			double feel;
			vector<double> feelbase;
			for(int i=0; i<6; i++){
				f >> feel;
				feelbase.push_back(feel);
				char ctmp = f.get();
				if(ctmp == ','||ctmp == '\n'){}
				else	printf("File format is not available.\n");
			}
			tp.brain.setfeel(feelbase);
			Tuplebase.push_back(tp);//
			s = "";
			c1 = f.get(); 
		}else{
			s +=  c1;
			c1 = cpin;
		}
	}
	printf("[Tuple]:Information extracting done.\n");
}

void valid(string fname){
	fstream f(fname, ios::in);
	char c1, cpin;
	while((c1 = f.get()) != '\n');
	c1=f.get();
//	printf("[Tuple]:Cleaned head marks.\n");
	string s;
	while((cpin=f.get()) != EOF){
		if(cpin == ','){
			s += c1;
//			cout << s << endl;
			Validbase.push_back(s);
			char feel;
			for(int i=0; i<6; i++){
				f >> feel;
//				cout << feel << endl;
//				system("pause");
				char ctmp = f.get();
				if(ctmp == ','||ctmp == '\n'){}
				else	printf("File format is not available.\n");
			}
			s = "";
			c1 = f.get(); 
		}else{
			s +=  c1;
			c1 = cpin;
		}
	}
//	printf("[Tuple]:Information extracting done.\n");
}
