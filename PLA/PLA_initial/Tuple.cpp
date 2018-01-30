#include "tuple.h"
using namespace std;

vector<Tuple> Tuplebase;
vector<Tuple> Validbase;
vector<double> output;
// ture positive
int Tp, Fn, Tn,Fp;

void Tuple::Setx_(vector<double> x_set){
	xi = x_set;
}

bool Tuple::multiv(vector<double> &w_set, bool fix){
	vector<double> w = w_set;
	int size = w_set.size();
	double sign=0;
	
//	for(int i=0; i<w_set.size(); i++){
//		cout << w_set[i] << ' ';
//	}cout << endl;
	
	if(w_set.size() != xi.size())
		printf("w_set-size != x_set-size");
	else{
		for(int i=0; i<size; i++){
			sign += (xi[i] * w[i]);
		}
	}
	
	if(fix == false){
		cout << sign << endl;
	} 
	
	for(int i=0; i<size; i++){
		cout << w[i] << ' ';
	}cout << endl;
	
	if((sign*label) > 0){
		if(sign > 0)	Tp++;
		else Tn++;
		
		return true;
	}else{
		if(sign > 0)	Fp++;
		else	Fn++;
		if(fix){
			for(int i=0; i<size; i++){
				double insert = label * xi[i];
				w_set[i] += insert;
			}
		}
		return false;
	}
}



