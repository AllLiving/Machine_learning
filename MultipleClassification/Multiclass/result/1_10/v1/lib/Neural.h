#ifndef NEURAL
#define NEURAL

#include <bits\stdc++.h>
using namespace std;

// design for every Neure element;
class Neure{
public:
	Neure();
//	Neure(double(*) (const double *));
	// In one neure, calculate sectional ans by attributes and active function;
	double Sprawl(const vector<double> &attrs, double(*)(const double&));
	// Fix degree about the neure
	bool Learn(double ratio = 1);
	double geterr();
	double getforetell();
	double getwgtnum();
	// collect Error data for current neure node
	double Errsum(const double&);
	// calculate diffrence of function about value;
	double diff(const double&);
	void dissec(); 
	
	Neure *next;
	vector<double> wgt;
	bool offspring;
	int wgtnum;
	
private:
	double bias;
	double error;
	double foretell;
	vector<double> attrset;
	double(*function)(const double& v);
};

// design for the net composed by neures;
class NeuNet{
public:
	NeuNet();
	// connect current layer and nextlayer;
	bool Propagate(Neure*);
	double Forepass(const vector<double> &attrs);
	bool Backpass(const double &);
	void Train(const vector<vector<double>> &, const vector<double> &, const int &);
	string Valid(const vector<vector<double>> &, const vector<double> &);
	void Test(const vector<vector<double>> &, const vector<double> &, const string &);
	double Loss();
	double Prophet();
	
	vector<Neure> neulayer;
	vector<Neure*> nxtlayer;
	//int neunum = 35;
	int neunum = 512;
};

#endif
