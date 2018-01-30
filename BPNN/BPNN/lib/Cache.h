#ifndef CACHE
#define CACHE

#include <bits\stdc++.h>
using namespace std;

class Tuple{
public:
	
	double label;
	vector<double> attr;
};


class Cache{
public:
	Cache(const string&, bool T=false);
	int getsize();
	int getattrnum();
	
	int Attrnum = 0;
	vector<Tuple> cachebase;
	vector<double> labelbase;
};

#endif












