#include "tuple.h"
using namespace std;

vector<string> vocbase;
vector<Tuple> Tuplebase;
vector<string> Validbase;

//	fill vocbase;
inline void Insert_vocbase(string voc){
	vector<string>::iterator it
		= find(vocbase.begin(), vocbase.end(), voc);
	if(it == vocbase.end()){
		vocbase.push_back(voc);
	}	
}
void Visit_vocbase(){
	printf("\n------------------------------\n");
	for(int i=0; i<vocbase.size(); i++){
		cout << vocbase[i] << ' ';
	}
	printf("\n------------------------------\n");
} 

//	convert every line into data and label;
//	fill vocbase in the process of dismantle;
inline void Tuple::Collectvoc(string s, bool fix_base)
{
	string voc;
	stringstream stm;
	stm << s;
	while(stm >> voc){
//		select different vocabulary;
		if(voc.find(',') < voc.length()){
			string voc_;
			for(int i=0; i<voc.length(); i++){
				if(voc[i] == ','){
					vca.push_back(voc_);
					if(fix_base)	Insert_vocbase(voc_);
					i++;
				}
				voc_ += voc[i];
			}
		}else{
			vca.push_back(voc);
			if(fix_base)	Insert_vocbase(voc);
		}
	}
}

//	with vocbase, update row data via "vca" and "vocbase";
inline void Tuple::Updaterow(){
	for(int i=0; i<vocbase.size(); i++){
		vector<string>::iterator it
			= find(vca.begin(), vca.end(), vocbase[i]);
		if(it == vca.end()){
			row.push_back(0);
		}else row.push_back(1);
	}
}

void Tuple::Register(string s){
	Collectvoc(s, false);
	Updaterow();
}

#define Manhattan
//#define Euclidean

//	calculate the distance of two tuple;
double Tuple::Distanceof(Tuple tup){
	vector<bool> a = row;
	vector<bool> b = tup.row;
	double dst = 0;
	#ifdef Manhattan
	for(int i=0; i<b.size(); i++){
		short av=0, bv=0;
		if(a[i] == true)	av=1;
		if(b[i] == true)	bv=1;
		dst = dst + (av-bv)*(av-bv);
	}
	return dst;
	#endif
	#ifdef Euclidean
	for(int i=0; i<b.size(); i++){
		short av=0, bv=0;
		if(a[i] == true)	av=1;
		if(b[i] == true)	bv=1;
		dst = dst + (av-bv)*(av-bv);
	}
	return sqrt(dst);
	#endif 
}
 
//	[Tuple]	feelbar + distance	=>	feels;
void Tuple::taste(int scope){
//	select the first several tuples;
	map<double, int> findtp;
	vector<double> cdst;
	int update_cdst = 0;
	for(int pin=0; pin<scope; pin++)	cdst.push_back(100);
	for(int tpin=0; tpin<Tuplebase.size(); tpin++){
		double dst = Distanceof(Tuplebase[tpin]);
		if(dst < cdst[cdst.size()-1]){
			update_cdst++;
			cdst.push_back(dst);
			findtp[dst] = tpin;
			sort(cdst.begin(), cdst.end());
			cdst.pop_back();
		}
	}
	if(update_cdst < scope){
		printf("[Tuple.cpp/taste]:Scope or distance is too big.\n");
		printf("[Tuple.cpp/taste]:Program abort.\n");
		exit(0);
	}
	
	vector<double> fb;
	for(int i=0; i<6; i++){
		double fp = 0;
		for(int dstpin=0; dstpin<cdst.size(); dstpin++){
			double dst=cdst[dstpin];
			int tpin = findtp[dst];
			if(Distanceof(Tuplebase[tpin]) == 0){
				fp = 0;
				fp += Tuplebase[tpin].brain.feelbar[i];
				break;
			}else{
				double key_feel = Tuplebase[tpin].brain.feelbar[i];
				if(key_feel > 0.5){
					key_feel *= 1.5;
					key_feel = (int)(100*key_feel);
					key_feel /= 100;
				}else if(key_feel < 0.5){
					key_feel *= 0.3;
					key_feel = (int)(100*key_feel);
					key_feel /= 100;
				}
				fp = fp + key_feel/(0.01+Distanceof(Tuplebase[tpin]));
			}
		}
		fb.push_back(fp);
	}
	
	double sum = 0;
	for(int i=0; i<fb.size(); i++){
		fb[i] = (int)(100*fb[i]);
		fb[i] /= 100;
	}
	for(int i=0; i<fb.size(); i++)	sum += fb[i];
	for(int i=0; i<fb.size(); i++)	fb[i] = fb[i]/sum;
	brain.setfeel(fb);
}

//	check datas from tuples;
void Tuple::telescope(){
	for(int i=0; i<vca.size(); i++){
		cout << vca[i] << ' '; 
	}printf("\n");
}
