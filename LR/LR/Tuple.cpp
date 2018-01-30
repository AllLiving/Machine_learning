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
	double Hx = 1/(1+exp(-1*mtp/1000));
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

bool Tuple::Jury(vector<double> &w_set, bool fix){
	vector<double> w = w_set;
	double multp=mulvec(w_set, xi);
	double Hx = forHx(w_set, xi);
	
	int size = w_set.size();
	short sign = 0;
	if(Hx>0.5){
		output.push_back(1);
		if(label==1)	sign = 1;
	}else if(Hx<0.5){
		output.push_back(0);
		if(label==0)	sign = 1;
	}
	
	if(fix){
		for(int wpin=0; wpin<size; wpin++){
			double eta = abs( (Hx-label)*xi[wpin] );
//			printf("eta=%lf\n", eta);
//			if(eta==0){
//				printf("Hx=%lf\t", Hx);
//				printf("label=%d\t", label);
//				printf("xi=%lf\n", xi[wpin]);
//			}
//			double eta = 10.5; 
			w_set[wpin] -= eta*(Hx-label)*xi[wpin];
		}
//		printf("w[0]=%lf\n", w_set[0]);
	}
	
	if(sign){
		return true;
	}else{
		return false;
	}
}
