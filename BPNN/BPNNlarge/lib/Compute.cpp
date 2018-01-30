#include <bits\stdc++.h>
#include "Compute.h"
using namespace std;

//#define debug
double sigmoid(const double &value){
	#ifdef debug
	
	#endif
	double v = exp(-1*value/30);
	return 1/(1+v);
}

double plain(const double &value){
	return value;
}

vector<bool> dectobi(const int& num_){
	int num = num_;
	stack<short> bit;
	while(num/2){
		bit.push(num%2);
		num /= 2;
	}
	bit.push(num);
	
	vector<bool> seq;
	while(!bit.empty()){
		if(bit.top()==1){
			seq.push_back(true);
		}else{
			seq.push_back(false);
		}
		bit.pop();
	}
	return seq;
}

int bitodec(const vector<bool> &seq){
	int len = seq.size();
	int w = 1;
	int ans=0;
	for(int i=(len-1); i>=0; i--, w*=2){
		if(seq[i]){
			ans += w*1;
		}
	}
	return ans;
}
