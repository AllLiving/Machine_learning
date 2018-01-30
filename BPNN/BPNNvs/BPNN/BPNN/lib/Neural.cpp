#include <bits\stdc++.h>
#include "Neural.h"
#include "Compute.h"
using namespace std;

//#define fore
//#define back

static void dvd(){
	printf("\n");
	for(int i=0; i<20; i++){
		printf("-");
	}printf("\n");
}

Neure::Neure(){
//	printf("[Neure]:Preparing neure...\n");
	next = NULL;
	offspring=false;
	wgtnum = 5;
	for(int i=0; i<wgtnum; i++){
		wgt.push_back(1);
	}
	error = 0;
	bias = 1;
	foretell = 0;
//	printf("[Neure]:A neure created.\n");
}

void Neure::dissec(){
	dvd();
	printf("=====IS CHECKING...=====\n");
	printf("Foretell last time=%lf\n", foretell);
	printf("error=%lf\n", error); 
	if(offspring){
		printf("With offspring.\n");
	}else{
		printf("Without offspring.\n");
	}
	printf("Bias = %lf\n", bias);
	if(wgtnum > 30){
		printf("wgt num=");
		cout << wgtnum << ' ';
		printf("It's a empty!\n");
	}else{
		printf("And wgt check is below:\n");
		for(int i=0; i<wgtnum; i++){
			cout << wgt[i] << endl;
		}
	}
	printf("=====CHECK DONE=====\n");
	dvd();
	system("pause");
}

double Neure::Sprawl(const vector<double> &attrs, double(*func)(const double&)){
//	printf("[Neure]:Begin Sprawl...\n");
	double sum=0;
	wgtnum = attrs.size();
	attrset = attrs;
	
	for(int atpin=0; atpin<attrs.size(); atpin++){
		double crt_attr = attrs[atpin];
		sum += wgt[atpin]*crt_attr;
	}
	sum += bias;
	double ans = func(sum);
	function = func;
	foretell = ans;
	return ans;
}

double Neure::geterr(){return error;}
double Neure::getforetell(){return foretell;}
double Neure::getwgtnum() { return wgtnum; }

double Neure::Errsum(const double& real){
	if(offspring){
		double curerr = next->geterr();
		#ifdef back
		printf("[Neure]Errsum:Begin error...\n");
		printf("[Neure]Errsum:exist offspring...\n");
		dvd();
		printf("[Neure]Errsum:The next layer %d wgts:\n", next->wgtnum);
		for(int wpin=0; wpin<next->wgtnum; wpin++){
			cout << next->wgt[wpin] << endl;
		}
		dvd();
		printf("cuurent err=%lf\n", curerr);
		printf("[Neure]Errsum:Sum done: error=%lf\n", error);
		#endif
		error += curerr;
	}else{
		#ifdef back
		printf("[Neure]Errsum:Begin error...\n");
		printf("[Neure]Errsum:no offspring...\n");
		printf("[Neure]Errsum:Sum done: error=%lf\n", error);
		#endif
		error = real - foretell;
	}
	return error;
}

double Neure::diff(const double& v){
	if(function == sigmoid){
		return v*(1-v);
	}else if(function == plain){
		return 1;
	}
	return 1;
}

bool Neure::Learn(double ratio){
	#ifdef back
	printf("[NeuNet]Learn:Begin learn...\n");
	#endif
//	printf("wgtnum=%d\n", wgtnum);
	for(int wpin=0; wpin<wgtnum; wpin++){
		double err = geterr();
		double prt = diff(foretell);
		wgt[wpin] += 0.9 * attrset[wpin] * err * prt; 
	}
	bias += 0.9 * geterr() * diff(foretell);
	
	#ifdef back
	dvd();
	printf("[NeuNet]Learn:After updadte wgt below:\n");
	for(int wpin=0; wpin<wgtnum; wpin++){
		printf("%lf\n", wgt[wpin]);
	}
	cout << bias << endl;
	printf("wgtnum=%d\n", wgtnum);
	dvd();
	#endif
	return true;
} 

NeuNet::NeuNet(){
//	printf("[NeuNet]:Initializing net...\n");
	neunum = 10;
	neulayer.clear();
	for(int i=0; i<neunum; i++){
		Neure neu;
		neu.next = new Neure();
		neulayer.push_back(neu);
	}
	nxtlayer.clear();
	Neure *neu = new Neure();
	nxtlayer.push_back(neu);
	
//	printf("[NeuNet]:Finish Initialization.\n");
}

bool NeuNet::Propagate(Neure *neu){
//	printf("[NeuNet]Propagate:Begin Propagating...\n");
	
	nxtlayer.pop_back();
	nxtlayer.push_back(neu);
	
	for(int npin=0; npin<neulayer.size(); npin++){
		
		neulayer[npin].next = (neu);
		neulayer[npin].offspring = true;
	}
//	printf("[NeuNet]Propagate:Propagate done.\n");
	return true;
}

double NeuNet::Forepass(const vector<double> &attrs){
	vector<double> hidop; 
	for(int npin=0; npin<neulayer.size(); npin++){
		double hidot = neulayer[npin].Sprawl(attrs, sigmoid);
		hidop.push_back(hidot);
	}
	
	#ifdef fore
	printf("[NeuNet]Forepass:Begin forepass...\n");
	dvd();
	printf("[NeuNet]Forepass:Any forewall node has wgts:\n");
	for(int wpin=0; wpin<neulayer[0].getwgtnum(); wpin++){
		cout << neulayer[0].wgt[wpin] << endl;
	}
	printf("[NeuNet]Forepass:Spark from first wall:\n");
	for(int hpin=0; hpin<hidop.size(); hpin++){
		cout << hidop[hpin] << '\n';
	}
	dvd();
	#endif
	
	double predict;
	if(neulayer[0].offspring == false){
		Neure *out = new Neure();
		predict = out->Sprawl(hidop, sigmoid);
		Propagate(out);
		#ifdef fore
		printf("[NeuNet]Forepass:Building backwall...\n");
		printf("[NeuNet]Forepass:Any backwall node has wgts:\n");
		for(int wpin=0; wpin<nxtlayer[0]->getwgtnum(); wpin++){
			cout << nxtlayer[0]->wgt[wpin] << endl;
		}
		#endif
	}else{
		#ifdef fore
		printf("[NeuNet]Forepass:Backwall calculating...\n");
		printf("[NeuNet]Forepass:Any backwall node has wgts:\n");
		for(int wpin=0; wpin<neulayer[0].wgtnum; wpin++){
			cout << neulayer[0].wgt[wpin] << endl;
		}
		#endif
		predict = nxtlayer[0]->Sprawl(hidop, sigmoid); 
		for (int npin = 0; npin<neulayer.size(); npin++) {
			neulayer[npin].next = (nxtlayer[0]);
			neulayer[npin].offspring = true;
		}
	}

	#ifdef fore
	dvd();
	printf("[NeuNet]Forepass:Thus we predict:");
	cout << predict << endl;
	dvd();
	printf("[NeuNet]Forepass:Forepass done.\n");
	dvd();
	printf("[NeuNet]Forepass:Thus we predict\n%lf", predict);
	dvd();
	#endif
	return predict;
}

bool NeuNet::Backpass(const double &real){
	#ifdef back
	printf("[NeuNet]Backpass:Begin backpass...\n");
	printf("[NeuNet]Backpass:Backwall neures learning...\n");
	printf("[NeuNet]Backpass:%d neures waiting to learn...\n", nxtlayer.size());
	printf("CHECK backpass backwall...\n");
	#endif
	for(int xpin=0; xpin<nxtlayer.size(); xpin++){
		nxtlayer[xpin]->Errsum(real);
		nxtlayer[xpin]->Learn();
	}
	
	#ifdef back
	printf("[NeuNet]Backpass:Backwall neures learn done.\n");
	printf("[NeuNet]Backpass:Forewall neures learning...\n");
	printf("[NeuNet]Backpass:%d neures wait to learn...\n", neulayer.size());
	#endif
	
	for(int npin=0; npin<neulayer.size(); npin++){
		neulayer[npin].Errsum(real);
		neulayer[npin].Learn();
	}
	
	#ifdef back
	printf("[NeuNet]Backpass:Forekwall neures learn done\n");
	printf("[NeuNet]Backpass:Backpass done.\n");
	#endif
	return true;
}

double NeuNet::Loss(){
//	printf("[NeuNet]Loss:Lossing begining...\n");
	double losum=0;
//	printf("nxtlayer size=%d\n", nxtlayer.size());
	for(int npin=0; npin<nxtlayer.size(); npin++){
//		Neure* crt = new Neure();
//		crt = nxtlayer[npin];
//		crt->Errsum(16);
//		printf("error=%d\n", crt->geterr());
		losum += nxtlayer[npin]->geterr();
	}
//	printf("[NeuNet]Loss:Lossing done.\n");
	return losum;
}











