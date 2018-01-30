#include<iostream>
#include<bits\stdc++.h>
#include"lib\Comment.h"
#include"lib\Filestream.h"
#include"lib\Compute.h"
#include"lib\Neural.h"
using namespace std;
#define allsize
#define test

int main() {
	InitComma();

	NeuNet net;
	Filestream f("MulLabelTrainhalf.ss");
	//Filestream f("MulLabelTest.ss");

	vector<string> keys;
	for (unsigned int kpin = 0; kpin < keybase.size(); kpin++) {
		if (keycnt[kpin] > mstFreq / 15) {
			keys.push_back(keybase[kpin]);
		}
	}
	keybase = keys;

	printf("[main]train:Read done.\n");
	vector<string> tmp = keybase;
	vector<double> levels;
	unsigned int scale = 1;
	for (int cnt = 0; cnt < 5; cnt++) {
		printf("[main]train:%d times.\n", cnt);
		vector<vector<double>> matrix;
		matrix = f.getCmtMtx();
		levels = f.getLevel();
#ifdef allsize
			scale = matrix.size();
#endif // allsize
		for (unsigned int mpin = 0; mpin < scale; mpin++) {
			vector<double> crtv = matrix[mpin];
			net.Forepass(crtv);
			double standard = levels[mpin];
			net.Backpass(standard);
		}
	}
	printf("[main]train:train done.\n");

	printf("[main]valid:Is predicting...\n");
	Filestream fv("MulLabelTest.ss", false);
	//Filestream fv("MulLabelTrain.ss", false);
	fstream fout("fout.csv", ios::out);
	vector<vector<double>> matrix = fv.getCmtMtx();
	levels = fv.getLevel();
	unsigned int wholesize = 0;
	unsigned int shoot = 0;
#ifdef allsize
	scale = matrix.size();
#endif // allsize
	for (unsigned int mpin = 0; mpin < scale; mpin++) {
		vector<double> crtv = matrix[mpin];
		double standard = levels[mpin];
		net.Forepass(crtv);
		double ans;
		ans = net.Prophet();
		//ans = amply(ans);
		double tmp = ans;
		cout << mpin+1 << ':' << ans << '\t' << forLevel(ans) << endl;
		if (forLevel(ans) == forLevel(standard))
			shoot++;
#ifdef test
		fout << forLevel(ans) << "\n";
#endif // test
		wholesize++;
	}

#ifndef test
	printf("[main]:shoot=%d\n", shoot);
	printf("[main]:accurancy=%lf\n", (double) shoot/ wholesize);
#endif // test
	printf("[main]:shoot=%d\n", shoot);
	printf("[main]train:done.\n");
	printf("\n");	system("pause");
	return 0;
}