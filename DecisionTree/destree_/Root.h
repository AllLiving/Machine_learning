#include <bits/stdc++.h>
#include "Cmpute.h"

using namespace std;

class Root{
public:
	Root();
	bool build(vector<vector<int>> Attr_set, vector<int> label); 
	int getans(vector<int> attribute);
	void climb(string path);
	
	vector<int> label;
	vector<int> attr_set;
	vector<int> branch_option; 
	vector<Root*> kidergarden; 
	int attr_index;
	int ans;
	bool leafans; 
};
