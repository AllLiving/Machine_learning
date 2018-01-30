#include <bits/stdc++.h>
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
	void taste();
	
	vector<bool> row;
	vector<string> voca;
	string label;
};

extern vector<string> vocbase;
extern vector<Tuple> Tuplebase;
extern vector<string> Validbase;
extern void Visit_vocbase();
extern void train(string fname);
extern void valid(string fname);
extern vector<string> labelbase;
extern vector<string> allabel;
