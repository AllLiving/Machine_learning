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
	}
}
int main(int argc, char** argv) {
	
	Cache train("train.csv");
	cout << train.getsize() << endl;
	
	printf("[main]:Testing %d datas.\n", train.cachebase.size());
	NeuNet net;
	for(int i=0; i<300; i++){
		for (int cpin=0; cpin<train.cachebase.size(); cpin++){
			Tuple crt = train.cachebase[cpin];
			net.Forepass(crt.attr);
			net.Backpass(crt.label);
		}
	}

	Cache valid("test.csv", true);
	printf("[main]:Is testing...\n");
	for (int cpin = 0; cpin<valid.getsize(); cpin++) {
		Tuple crt = valid.cachebase[cpin];
		showv(crt.attr);
		net.Forepass(crt.attr);
		cout << "predict:" << net.nxtlayer[0]->getforetell() << endl;
	}
	return 0;
}






