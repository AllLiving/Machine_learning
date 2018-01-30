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
	error = 0;
	bias = 2.2;
	foretell = 1;
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

// In one neure, calculate sectional ans by attributes and active function;
double Neure::Sprawl(const vector<double> &attrs, double(*func)(const double&)){
//	printf("[Neure]:Begin Sprawl...\n");
	double sum=0;
	wgtnum = attrs.size();
	attrset = attrs;
	
// Initial wgt sequence according to attribute size;
	if (wgt.size() < attrs.size())
	{
#ifdef  back
		printf("[NeuNet]Sprawl:Is Initializing wgt sequence.\n");
#endif //  back
		wgt.clear();
		for (unsigned int wpin = 0; wpin < attrs.size(); wpin++) {
			wgt.push_back(wpin/10000);
		}
	}

	for(unsigned int atpin=0; atpin<attrs.size(); atpin++){
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

// collect Error data for current neure node
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
		error = curerr;
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

// calculate diffrence of function about value;
double Neure::diff(const double& v){
	if(function == sigmoid){
		return v*(1-v);
	}else if(function == plain){
		return 1;
	}
	return 1;
}

// Fix degree about the neure
bool Neure::Learn(double ratio){
	#ifdef back
	printf("[NeuNet]Learn:Begin learn...\n");
	#endif
	for(int wpin=0; wpin<wgtnum; wpin++){
		double err = geterr();
		double prt = diff(foretell);
		double fix = ratio * attrset[wpin] * err * prt
			* abs(attrset[wpin] * err * prt) / wgt.size();
					/// wgt.size() / wgt.size() 
		wgt[wpin] += fix;
	}
	bias += ratio * geterr() * diff(foretell)
		* abs(geterr() * diff(foretell)) / wgt.size() ;
	
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

// connect current layer and nextlayer;
bool NeuNet::Propagate(Neure *neu){
	nxtlayer.clear();
	nxtlayer.push_back(neu);
	
	for(unsigned int npin=0; npin<neulayer.size(); npin++){
		neulayer[npin].next = (neu);
		neulayer[npin].offspring = true;
	}
	return true;
}

// Forepass action
double NeuNet::Forepass(const vector<double> &attrs){
	vector<double> hidop; 
	for(unsigned int npin=0; npin<neulayer.size(); npin++){
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
		if (nxtlayer[0] == NULL)
		{
			printf("[Nurtral]Forepass:Initialize wrong somewhere.\n");
			system("pause");
		}
		predict = nxtlayer[0]->Sprawl(hidop, plain); 
		for (unsigned int npin = 0; npin<neulayer.size(); npin++) {
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
	for(unsigned int xpin=0; xpin<nxtlayer.size(); xpin++){
		nxtlayer[xpin]->Errsum(real);
		nxtlayer[xpin]->Learn((1+xpin*xpin)*nxtlayer.size());
	}
	
	#ifdef back
	printf("[NeuNet]Backpass:Backwall neures learn done.\n");
	printf("[NeuNet]Backpass:Forewall neures learning...\n");
	printf("[NeuNet]Backpass:%d neures wait to learn...\n", neulayer.size());
	#endif
	
	for(unsigned int npin=0; npin<neulayer.size(); npin++){
		neulayer[npin].Errsum(real);
		neulayer[npin].Learn((1+npin)*neulayer.size());
	}
	
	#ifdef back
	printf("[NeuNet]Backpass:Forekwall neures learn done\n");
	printf("[NeuNet]Backpass:Backpass done.\n");
	#endif
	double predict = nxtlayer[0]->getforetell();
	if (sameLayer(predict, real)) {
		return false;
	}
	return true;
}

void NeuNet::Train(const vector<vector<double>> &matrix, const vector<double> &levels, const int &iterator) {

	printf("[main]train:Iterator %d times totally.\n", iterator);
	for (int cnt = 0; cnt < iterator; cnt++) {
		printf("[main]train:%d times.\n", cnt);
		//vector<vector<double>> adamatrix;
		vector<vector<double>> higmatrix;
		vector<vector<double>> midmatrix;
		vector<vector<double>> lowmatrix;
		//vector<double> adalevels;
		vector<double> higlevels;
		vector<double> midlevels;
		vector<double> lowlevels;
		for (unsigned int mpin = 0; mpin < matrix.size(); mpin++) {
			vector<double> crtv = matrix[mpin];
			Forepass(crtv);
			double standard = levels[mpin];
			bool ada = Backpass(standard);
			//if (ada && cnt < (iterator - 10) && cnt > 20) {
			//	//adamatrix.push_back(crtv);
			//	//adalevels.push_back(standard);
			//	if (standard > 0.6) {
			//		higmatrix.push_back(crtv);
			//		higlevels.push_back(standard);
			//	}
			//	else if (standard > 0.3) {
			//		midmatrix.push_back(crtv);
			//		midlevels.push_back(standard);
			//	}
			//	else {
			//		lowmatrix.push_back(crtv);
			//		lowlevels.push_back(standard);
			//	}
			//}
		}
		// prepare for adaboost strong exersice
		int higcnt = higlevels.size();
		int midcnt = midlevels.size();
		int lowcnt = lowlevels.size();
		int adacnt = min(higcnt, midcnt);
		adacnt = min(adacnt, lowcnt);

		// strong training...
		//for (unsigned int apin = 0; apin < adacnt; apin++) {
		//	// to hig tuple;
		//	for (unsigned short tpin = 0; tpin < 5; tpin++) {
		//		vector<double> crtv = higmatrix[apin];
		//		Forepass(crtv);
		//		double standard = higlevels[apin];
		//		Backpass(standard);
		//	}
		//	// for mid ones;
		//	for (unsigned short tpin = 0; tpin < 5; tpin++) {
		//		vector<double> crtv = midmatrix[apin];
		//		Forepass(crtv);
		//		double standard = midlevels[apin];
		//		Backpass(standard);
		//	}
		//	// for others;
		//	for (unsigned short tpin = 0; tpin < 5; tpin++) {
		//		vector<double> crtv = lowmatrix[apin];
		//		Forepass(crtv);
		//		double standard = lowlevels[apin];
		//		Backpass(standard);
		//	}
		//}
	}
	printf("[main]train:train done.\nCongratulation!\n");
}

string NeuNet::Valid(const vector<vector<double>> &matrix, const vector<double> &levels) {
	unsigned int hig = 0;
	unsigned int mid = 0;
	unsigned int low = 0;

	unsigned int higShoot = 0;
	unsigned int midShoot = 0;
	unsigned int lowShoot = 0;

	for (unsigned int mpin = 0; mpin < matrix.size(); mpin++) {
		vector<double> crtv = matrix[mpin];
		double standard = levels[mpin];
		Forepass(crtv);
		double ans = Prophet();

		if (standard < 0.1) {
			low++;
			if (forLevel(ans) == "LOW")
				lowShoot++;
		}
		else if (standard < 0.6) {
			mid++;
			if (forLevel(ans) == "MID")
				midShoot++;
		}
		else if (standard < 1.3) {
			hig++;
			if (forLevel(ans) == "HIG")
				higShoot++;
		}
	}

	string validlog;
	stringstream ss;
	string tmp;
	ss << higShoot;
	ss >> tmp;
	validlog += tmp;
	validlog += "_";
	ss << midShoot;
	ss >> tmp;
	validlog += tmp;
	validlog += "_";
	ss << lowShoot;
	ss >> tmp;
	validlog += tmp;
	validlog += "_";

	return validlog;
}

void NeuNet::Test(const vector<vector<double>> &matrix, const vector<double> &levels, const string &filename) {
	fstream fout(filename + ".csv", ios::out);
	for (unsigned int mpin = 0; mpin < matrix.size(); mpin++) {
		vector<double> crtv = matrix[mpin];
		double standard = levels[mpin];
		Forepass(crtv);
		double ans = Prophet();

		fout << forLevel(ans) << "\n";
	}
}

double NeuNet::Prophet() {
	double predict = nxtlayer[0]->getforetell();
	return predict;
}

double NeuNet::Loss(){
//	printf("[NeuNet]Loss:Lossing begining...\n");
	double losum=0;
//	printf("nxtlayer size=%d\n", nxtlayer.size());
	for(unsigned int npin=0; npin<nxtlayer.size(); npin++){
//		Neure* crt = new Neure();
//		crt = nxtlayer[npin];
//		crt->Errsum(16);
//		printf("error=%d\n", crt->geterr());
		losum += nxtlayer[npin]->geterr();
	}
//	printf("[NeuNet]Loss:Lossing done.\n");
	return losum;
}