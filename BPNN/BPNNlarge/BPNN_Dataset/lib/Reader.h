#ifndef AROYA_READER
#define AROYA_READER

#include<vector>
using namespace std;

class Reader {
public:
	Reader(const char*);
	//~Reader();
	vector<double*>data;
	vector<int>flag;
	double persents(double*, bool display = 0);
	int columns, rows;
};

#endif