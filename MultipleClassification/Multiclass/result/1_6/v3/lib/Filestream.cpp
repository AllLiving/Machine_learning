#include<bits\stdc++.h>
#include<iostream>
#include"Filestream.h"
#include"Comment.h"
using namespace std;

Filestream::Filestream(){}
Filestream::~Filestream(){}

Filestream::Filestream(const string &filename, const bool &expandKeyBase) {
	unicodeHell(filename);
	fstream fin("Filetrain.ss", ios::in);
	char c;
	string buffer;
	bool ender = false;
	while ((c = fin.get()) != EOF){
		ender = false;
		if (c == '\n') {
			ender = true;
			SerialComment cmt(buffer, expandKeyBase);
			userlist.push_back(cmt);
			lines++;
			buffer.clear();
		}
		else {
			buffer += c;
		}
	}
	if (!ender) {
		SerialComment cmt(buffer, expandKeyBase);
		lines++;
		userlist.push_back(cmt);
	}
}

void Filestream::unicodeHell(const string &filename) {
	fstream ftrain("Filetrain.ss", ios::out);
	fstream fin(filename, ios::in);
	char c;
	while ((c=fin.get()) != EOF){
		ftrain << c;
	}
}

vector<vector<double>> Filestream::getCmtMtx() {
	vector<vector<double>> cmt;
	for (unsigned int lpin = 0; lpin < userlist.size(); lpin++) {
		SerialComment scmt = userlist[lpin];
		cmt.push_back(scmt.getDigits());
		levelist.push_back(scmt.getLevel());
	}
	return cmt;
}

vector<double> Filestream::getLevel() {
	return levelist;
}