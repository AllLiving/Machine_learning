#include <bits\stdc++.h>
#include "Compute.h"
using namespace std;

//#define debug
double sigmoid(const double &value){
	#ifdef debug
	
	#endif
	double v = exp(-1*value);
	return 1/(1+v);
}

double plain(const double &value){
	return value;
}

double amply(const double &value) {
	double v = value;
	if (value > 0.5)	v = exp(value - 0.5);
	else if (value < 0.5)	v = -1 * exp(0.5 - value);
	return sigmoid(v);
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

vector<double> wordFreq(const vector<string> &Base, const vector<string> &Part) {
	vector<string> part = Part;
	vector<double> wordFreq;
	int whole = 0;
	for (unsigned int bpin = 0; bpin < Base.size(); bpin++) {
		string crts = Base[bpin];
		int wcnt = 0;
		wcnt = count(part.begin(), part.end(), crts);
		whole += wcnt;
		wordFreq.push_back(wcnt);
	}
	for (int wpin = 0; wpin < wordFreq.size(); wpin++) {
		if(whole)
			wordFreq[wpin] /= whole;
	}
	return wordFreq;
}

#define lowbound 0.411
#define highbound 0.619

string forLevel(const double &value) {
	if (value < lowbound) {
		return "LOW";
	}
	else if (value < highbound) {
		return "MID";
	}
	else if (value > highbound) {
		return "HIG";
	}
	printf("[Compute]forLevel:predict value is out of range.\n");
	system("pause");
}

bool sameLayer(const double &num1, const double &num2) {
	if (forLevel(num1) == forLevel(num2)) {
		return true;
	}
	return false;
}