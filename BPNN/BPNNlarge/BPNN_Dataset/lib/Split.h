#ifndef SPLIT
#define SPLIT
#include <bits\stdc++.h>
using namespace std;

// split .csv file into two files,
// interval is the ratio of the datasize from the two file,
// tail is designed for file suffix
bool split(const string filename, const string file1, const string file2, const int interval);

/*
string filename;
printf("[Split]: Your file name:");
cin >> filename;
printf("[SPlit]: The ratio of two filesize:");
int ratio;	cin >> ratio;
printf("[Split]: The name of first file to create:");
string file1;	cin >> file1;
printf("[Split]: The name of second file to create:");
string file2;	cin >> file2;

bool ans = split(filename, file1, file2, ratio);
*/

#endif