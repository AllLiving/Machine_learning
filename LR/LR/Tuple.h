#include <bits/stdc++.h>
using namespace std;

class Tuple{
public:
	
	void Setx_(vector<double> x_set);
	vector<double> Getx_();
	bool Jury(vector<double> &w_set, bool fix);
	
	short label;
private:
	vector<double> xi;
};

extern int Attrnum;
extern vector<int> output;
extern vector<Tuple> Tuplebase;
extern vector<Tuple> Validbase;
extern void train(string fname);
extern void valid(string fname);
extern double mulvec(vector<double> weight,vector<double> xvec);
extern double forHx(vector<double> weight,vector<double> xvec);
