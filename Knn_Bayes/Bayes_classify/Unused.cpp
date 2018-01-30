#include "Tuple.h"
#include "Emlabel.h"
using namespace std;

void train(string fname){
	fstream f(fname, ios::in);
	char c1, cpin;
	while((c1 = f.get()) != '\n');
	c1=f.get();
	string s;
	while((cpin=f.get()) != EOF){
		if(cpin == ','){
			s += c1;
			string ll;
			f >> ll;
			
			Tuple tp;
			tp.Collectvoc(s, true);
			tp.label = ll;
			fillemlabel(tp.label, tp.voca);
			Tuplebase.push_back(tp);
			
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
			Validbase.push_back(s);
			s = "";
			string sjunk;	f >> sjunk;
			c1 = f.get(); 
		}else{
			s +=  c1;
			c1 = cpin;
		}
	}
}
