#include <bits/stdc++.h>
#include "Unused.h"
using namespace std;

extern double entropy(vector<int> sequence);
double gini(vector<int> sequence);
extern vector<int> attr_filter(vector<int> attribute);
double attr_entropy(vector<int> attribute, vector<int> label);

double infogain(vector<int> attribute, vector<int> label);
double inforatio(vector<int> attribute, vector<int> label);
double syn_gini(vector<int> attribute, vector<int> label);

extern int forans(vector<int> v);
extern string tostring(int num);

extern int near_branch(int num, vector<int> branches);
