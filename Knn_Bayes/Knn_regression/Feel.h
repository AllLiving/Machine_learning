#include <bits/stdc++.h>
using namespace std;

class Feel{
public:
	void setfeel(vector<double> feelbase);
//	debug
	void visit_feelbar();
	vector<double> feelbar;
private:
	double anger;
	double disgust;
	double fear;
	double joy;
	double sad;
	double surprise;
};
extern vector<double> output;
