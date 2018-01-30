#include "tuple.h"
#include "Emlabel.h"
using namespace std;

vector<string> vocbase;
vector<Tuple> Tuplebase;
vector<string> Validbase;
vector<string> labelbase;
vector<string> allabel;

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
					voca.push_back(voc_);
					if(fix_base)	Insert_vocbase(voc_);
					i++;
				}
				voc_ += voc[i];
			}
		}else{
			voca.push_back(voc);
			if(fix_base)	Insert_vocbase(voc);
		}
	}
}

//	with vocbase, update row data via "voca" and "vocbase";
inline void Tuple::Updaterow(){
	for(int i=0; i<vocbase.size(); i++){
		vector<string>::iterator it
			= find(voca.begin(), voca.end(), vocbase[i]);
		if(it == voca.end()){
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
 
void Tuple::taste(){
	
	string emset[]={"joy", "sad", "disgust", "surprise", "anger", "fear"};
	vector<double> embar;
	for(int empin=0; empin<labelbase.size(); empin++){
		double chance = 1;
		string crt_em = emset[empin];
//		printf("crt_em:");	cout << crt_em << endl;
		for(int vpin=0; vpin<voca.size(); vpin++){
			string crt_v = voca[vpin];
//			printf("crt_v:");	cout << crt_v << endl;
			int numofv = count_words(crt_em, crt_v);
			int rptcnt = get_size(crt_em, true);
			int nrptcnt = get_size(crt_em, false);
			double tmpp = (double)(numofv+1)/(rptcnt + vocbase.size());
//			double tmpp = (double)(numofv+1)/(rptcnt + nrptcnt);
			chance = chance * tmpp;
		}
		int numofcrt_em = count(allabel.begin(), allabel.end(), crt_em);
		double rdio = (double)numofcrt_em/allabel.size();
		chance *= rdio;
		embar.push_back(chance);
	}
	
	double emsum=0;
	for(int i=0; i<labelbase.size(); i++)	emsum+=embar[i];
	for(int i=0; i<labelbase.size(); i++){
		embar[i]/= emsum;
	}
	
	double maxem = embar[0];
	int maxpin = 0;
	cout << emset[0] << ':' << embar[0] << '\n';
	for(int i=1; i<embar.size(); i++){
		cout << emset[i] << ':' << embar[i] << '\n';
		double crt_em = embar[i];
		if(crt_em >= maxem){
			maxem = crt_em;
			maxpin = i;
		}
	}
	label = emset[maxpin];
	cout << label << endl;
}

//	check datas from tuples;
void Tuple::telescope(){
	for(int i=0; i<voca.size(); i++){
		cout << voca[i] << ' '; 
	}cout << endl;
//	printf(":");	cout << label << endl;
}
