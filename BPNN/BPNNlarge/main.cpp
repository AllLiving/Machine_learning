#include <bits\stdc++.h>
#include "lib\Cache.h"
#include "lib\Neural.h"
#include "lib\Compute.h"
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void showv(vector<double> v){
	printf("\n[Show v]:size=%d\n", v.size());
	for(int i=0; i<v.size(); i++){
		printf("%lf\n", v[i]);
	}cout << endl;
}
#define set
int main(int argc, char** argv) {
	
	#ifndef set
	NeuNet net;
	Cache ftl("test.csv", true);
	printf ("[main]:Is testing...\n");
	fstream fs("15352015_caogj.csv", ios::out);
	for (int cpin = ftl.getsize() - 20; cpin<ftl.getsize(); cpin++) {
		Tuple crt = ftl.cachebase[cpin];
		net.Forepass(crt.attr);
		//net.Backpass(crt.label);
		fs << crt.label << ',' << (int)(net.nxtlayer[0]->getforetell()) << '\n';
	}
	system("pause");
//	double raw[]={1, 1, 0, 0, 6, 0, 1, 0.2879, 0.81};
//	vector<double> attrset;
//	for(int atpin=0; atpin<9; atpin++){
//		attrset.push_back(raw[atpin]);
//	}
////	showv(attrset);
//	double label = 16;
//	
//	NeuNet net;
//	for(int cnt=0; cnt<15; cnt++){
//		int ans;
//		printf("[main]:preparing forepass...\n");
//		ans = net.Forepass(attrset);
////		printf("[main]: dissec...\n");
////		net.nxtlayer[0]->dissec();
//		net.Backpass(16);
//		
//		printf("[main]:ans=%d\n", ans);
//		printf("Loss=%lf\n", net.Loss());
//		system("pause");
//	}
	
	#endif
	
	#ifdef set
	Cache train("train.csv");
	cout << train.getsize() << endl;
	
	printf("[main]:Testing %d datas.\n", train.cachebase.size());
	NeuNet net;
	fstream ft("Et.csv", ios::out);
	for(int i=0; i<300; i++){
		double E = 0;
		for (int cpin=0; cpin<train.cachebase.size(); cpin++){
			Tuple crt = train.cachebase[cpin];
			net.Forepass(crt.attr);
			net.Backpass(crt.label);
			
			E += abs(net.Loss());
		}
		//ft << E/train.cachebase.size() << endl;
		//printf("E=%lf\n", E/train.getsize());
	}

	/*fstream fsa("anst.csv", ios::out);
	for (int cpin = train.getsize()-20; cpin<train.getsize(); cpin++) {
		Tuple crt = train.cachebase[cpin];
		net.Forepass(crt.attr);
		net.Backpass(crt.label);
		fsa << crt.label << ',' << (int)(net.nxtlayer[0]->getforetell()) << '\n';
	}*/
	
//	system("pause");
	Cache valid("valid.csv");
	cout << valid.getsize() << endl;
	
	fstream fv("Ev.csv", ios::out);
	for(int i=0; i<300; i++){
		double E = 0;
		for (int cpin=0; cpin<valid.getsize(); cpin++){
			Tuple crt = valid.cachebase[cpin];
			net.Forepass(crt.attr);
			net.Backpass(crt.label);
			E += abs(net.Loss());
		}
		//fv << E/valid.getsize() << endl;
		//printf("E=%lf\n", E/valid.getsize());
	}

	printf("[main]:Is testing...\n");
	Cache ftl("tail.csv");
	fstream fs("ans.csv", ios::out);
	for (int cpin = 0; cpin<ftl.getsize(); cpin++) {
		Tuple crt = ftl.cachebase[cpin];
		net.Forepass(crt.attr);
		net.Backpass(crt.label);
		fs << crt.label << ','<< (int)(net.nxtlayer[0]->getforetell()) << '\n';
	}
	system("pause");
	#endif
	return 0;
}


















