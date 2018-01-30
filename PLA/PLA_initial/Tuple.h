#include <bits/stdc++.h>
using namespace std;
extern int Tp, Fn, Tn,Fp;

class Tuple{
public:
	
	void Setx_(vector<double> x_set);
	bool multiv(vector<double> &w_set, bool fix);
	
	short label;
private:
	vector<double> xi;
};

extern vector<Tuple> Tuplebase;
extern vector<Tuple> Validbase;
extern vector<double> output;
extern void train(string fname, int lines);
extern void valid(string fname, int lines);
