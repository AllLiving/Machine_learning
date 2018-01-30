#include<iostream>
#include<bits\stdc++.h>
#include"lib\Comment.h"
#include"lib\Filestream.h"
#include"lib\Compute.h"
#include"lib\Neural.h"
using namespace std;

unsigned int hig = 0;
unsigned int mid = 0;
unsigned int low = 0;

unsigned int higShoot = 0;
unsigned int midShoot = 0;
unsigned int lowShoot = 0;

void InitKeyBase() {
	vector<string> keys;
	for (unsigned int kpin = 0; kpin < keybase.size(); kpin++) {
		if (keycnt[kpin] > mstFreq / 100) {
			keys.push_back(keybase[kpin]);
		}
	}
	keybase = keys;
	printf("[main]train:Select %d nodes as input datas.\n", keybase.size());
}

void valid(NeuNet &net, const vector<vector<double>> &matrix, const vector<double> &levels, const string &filename) {
	printf("[main]valid:Is predicting...\n");
	//fstream fout(filename + ".csv", ios::out);
	for (unsigned int mpin = 0; mpin < matrix.size(); mpin++) {
		vector<double> crtv = matrix[mpin];
		double standard = levels[mpin];
		net.Forepass(crtv);
		double ans = net.Prophet();

		cout << mpin + 1 << ':' << ans << '\t' << forLevel(ans) << endl;

		if (standard < 0.1) {
			low++;
			if (forLevel(ans) == "LOW")
				lowShoot++;
		}
		else if (standard < 0.8) {
			mid++;
			if (forLevel(ans) == "MID")
				midShoot++;
		}
		else if (standard < 1.3) {
			hig++;
			if (forLevel(ans) == "HIG")
				higShoot++;
		}
		//fout << forLevel(ans) << "\n";
	}

	printf("[main]:hig/HIG=%d/%d\n", higShoot, hig);
	printf("[main]:mid/MID=%d/%d\n", midShoot, mid);
	printf("[main]:low/LOW=%d/%d\n", lowShoot, low);
	printf("[main]valid:done.\n");
}

#define TEST
//#define VALID

int main() {
	
	InitComma();

	NeuNet net;
	vector<double> levels;
	vector<vector<double>> matrix;
	printf("[log]:input node Freq/100;\nhiden nodes 380;\ntiny fix.  contrl adaboost train.\n");
	printf("[main]train:Is reading file for training...\n");
#ifdef VALID
	Filestream f("MulLabelTrainhalf.ss");
#endif // VALID
#ifdef TEST
	Filestream f("MulLabelTrain.ss");
#endif // TEST

	InitKeyBase();
	matrix = f.getCmtMtx();
	levels = f.getLevel();
	printf("[main]train:Read done.\n");

	vector<vector<double>> tmatrix;
	vector<double> tlevels;
	vector<vector<double>> vmatrix;
	vector<double> vlevels;
#ifdef TEST
	Filestream ft("MulLabelTest.ss", false);
	tmatrix = ft.getCmtMtx();
	tlevels = ft.getLevel();
#endif // TEST

#ifdef  VALID
	Filestream fv("MulLabelValid.ss", false);
	vmatrix = fv.getCmtMtx();
	vlevels = fv.getLevel();
#endif //  valid

	//int iterator;
	//printf("[main]train:How many times iterate:");
	//cin >> iterator;
	net.Train(matrix, levels, 115);
#ifdef TEST
	net.Test(tmatrix, tlevels, "out/fntinyfix");
#endif // TEST
#ifdef VALID
	valid(net, vmatrix, vlevels, "fout");
#endif // VALID
	
	printf("\n");	system("pause");/**/
	return 0;
}