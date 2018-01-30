#include <bits/stdc++.h>
#include "Feel.h"
using namespace std;

class Tuple{
public:
//	For updating;
	void Collectvoc(string s, bool fix_base);
	void Updaterow();
	void Register(string s);
//	For checking;
	void telescope();
	double Distanceof(Tuple tuple);
	void taste(int scope);
	
	vector<bool> row;
	vector<string> vca;
	Feel brain;
};

extern vector<string> vocbase;
extern vector<Tuple> Tuplebase;
extern vector<string> Validbase;
extern void Visit_vocbase();
extern void train(string fname);
extern void valid(string fname);
