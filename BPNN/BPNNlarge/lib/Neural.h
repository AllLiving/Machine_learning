#ifndef NEURAL
#define NEURAL

#include <bits\stdc++.h>
using namespace std;

class Neure{
public:
	Neure();
//	Neure(double(*) (const double *));
	double Sprawl(const vector<double> &attrs, double(*)(const double&));
	bool Learn(double ratio = 1);
	double geterr();
	double getforetell();
	double getwgtnum();
	double Errsum(const double&);
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

class NeuNet{
public:
	NeuNet();
	bool Propagate(Neure*);
	int Forepass(const vector<double> &attrs);
	bool Backpass(const double &);
	double Loss();
	
	vector<Neure> neulayer;
	vector<Neure*> nxtlayer;
	int neunum;
};

#endif
