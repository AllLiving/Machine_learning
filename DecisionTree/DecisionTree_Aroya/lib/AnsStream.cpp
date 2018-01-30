#include<fstream>
#include<iostream>
#include<vector>
using namespace std;
#include"AnsStream.h"

AnsStream::AnsStream(const vector<int>&ans) {
	length = ans.size();
	data = new int[length];
	for (int i = 0; i < length; i++)data[i] = ans[i];
	accuray = 0;
	recall = 0;
	precision = 0;
	f1 = 0;
}
void AnsStream::writeFile(const char*filename) {
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open()) {
		cout << "Cannot open " << filename << endl;
	}
	else {
		for (int i = 0; i < length; i++) {
			fout << data[i] << endl;
		}
	}
	fout.close();
}
void AnsStream::test(const vector<int>&flag, bool print) {
	if (flag.size() != length)cout << "flag.size() is not same as length of AnsStream!\n";
	else {
		int tt = 0, tf = 0, ft = 0, ff = 0;
		for (int i = 0; i < length; i++) {
			if (flag[i] > 0) {
				if (data[i] > 0)tt++;
				else tf++;
			}
			else {
				if (data[i] > 0)ft++;
				else ff++;
			}
		}
		accuray = double(tt + ff) / double(tt + tf + ft + ff);
		recall = double(tt) / double(tt + ft);
		precision = double(tt) / double(tt + tf);
		f1 = 2 * recall*precision / (precision + recall);
		if (print) {
			cout << "Accuray:" << accuray << endl;
			cout << "Recall:" << recall << endl;
			cout << "Precision:" << precision << endl;
			cout << "F1:" << f1 << endl;
		}
	}
}
double AnsStream::Accuray() { return accuray; }
double AnsStream::Precision() { return precision; }
double AnsStream::F1() { return f1; }
double AnsStream::Point() { return accuray; }