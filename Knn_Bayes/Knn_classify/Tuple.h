#include <bits/stdc++.h>
using namespace std;

class Tuple{
public:
//	For updating;
	void Dismantle(string s, bool fix_base);
	void Updaterow();
	void Register(string s);
//	For checking;
	void telescope();
	int rowsize(){
		return row.size();
	}
	double Distanceof(Tuple tuple);
	
	vector<double> row;
	vector<string> vca;
	string label;
};

extern vector<string> vocbase;
extern vector<string> category;
extern vector<Tuple> Tuplebase;
extern vector<string> wordbase;
extern vector<string> Forout_label;
extern void Visit_vocbase();
extern string classify(Tuple tp, int knn_scope);
