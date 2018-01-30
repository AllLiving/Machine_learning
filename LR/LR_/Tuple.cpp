#include "tuple.h"
using namespace std;

vector<Tuple> Tuplebase;
vector<Tuple> Validbase;
vector<int> output;
int Attrnum;

double mulvec(vector<double> weight, vector<double> xvec){
	if(weight.size() != xvec.size()){
		printf("[Tuple]/mulvec:w_set-size != x_set-size");
	}
	int size = weight.size();
	double multiple = 0;
	for(int i=0; i<size; i++){
		multiple += weight[i]*xvec[i];
	}
	return multiple;
}

double forHx(vector<double> weight,vector<double> xvec){
	double mtp = mulvec(weight, xvec);
	double Hx = 1/(1+exp(-1*mtp));
//	if((Hx==0)||(Hx==1)){
//		printf("[Tuple]/forHx:mtp=%lf\n", mtp);
//		printf("[Tuplecpp]/forHx:%.32lf\n", Hx);
//		system("pause");
//	}
	return Hx;
}

void Tuple::Setx_(vector<double> x_set){
	xi = x_set;
}

vector<double> Tuple::Getx_(){
	return xi;
}

bool Tuple::Jury(double &w0, vector<double> weight, vector<double> &w_set, bool fix){
	vector<double> w = weight;
	double multp=mulvec(weight, xi);
	double Hx = forHx(weight, xi);
//	printf("Hx=%.32lf\n", Hx);
//	system("pause");
	if(Hx == 0){
		printf("Hx=%lf\n", Hx);
		system("pause");
	}
	
	int size = weight.size();
	short sign = 0;
	if(Hx>0.5){
		output.push_back(1);
		if(fix == false)	printf("ans=1\n");
		if(label==1)	sign = 1;
	}else if(Hx<0.5){
		output.push_back(0);
		if(fix == false)	printf("ans=0\n");
		if(label==0)	sign = 1;
	}
	
	if(fix){
		w0 -= (Hx-label)*1;
		for(int wpin=0; wpin<size; wpin++){
			w_set[wpin] -= (Hx-label)*xi[wpin];
		}
	}
	
	if(sign){
		output.push_back(1);
		return true;
	}else{
		output.push_back(0);
		return false;
	}
}
