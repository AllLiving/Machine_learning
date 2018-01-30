#ifndef FILE
#define FILE
#include <bits\stdc++.h>
#include <iostream>
#include "Comment.h"
using namespace std;
class Filestream
{
public:
	Filestream(const string &, const bool &expandKeyBase = true);
	Filestream();
	~Filestream();
	void unicodeHell(const string &);
	vector<vector<double>> getCmtMtx();
	vector<double> getLevel();

	unsigned int lines;
private:

	vector<SerialComment> userlist;
	vector<double> levelist;
};

#endif // !FILE