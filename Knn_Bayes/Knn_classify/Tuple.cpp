#include "tuple.h"
using namespace std;

vector<string> vocbase;
vector<string> Forout_label;
vector<Tuple> Tuplebase;
vector<string> wordbase;

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
inline void Tuple::Dismantle(string s, bool fix_base)
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
					voc_ = "";
					i++;
				}
				voc_ += voc[i];
			}
			label = voc_;
		}else{
			vca.push_back(voc);
			if(fix_base)	Insert_vocbase(voc);
		}
	}
}

//	with vocbase, update row data via "vca" and "vocbase";
inline void Tuple::Updaterow(){
	vector<string> vocbase_ = vocbase;
	int vcasize = vca.size(), vspc=0;
	for(int i=0; i<vocbase_.size(); i++){
		bool appear = false;
		double cnt = 0;
		string crt_voc = vocbase_[i];
		for(int vpin=0; vpin<vcasize; vpin++){
			if(vocbase_[i] == vca[vpin]){
				cnt++;
			}
		}
		if(cnt != 0)	row.push_back(cnt/vcasize);
		else row.push_back(0);
	}
	double sum=0;
	for(int rpin=0; rpin<row.size(); rpin++){
		if(row[rpin] != 0)	sum += row[rpin];
	}
	for(int i=0; i<row.size(); i++){
		if(row[i] != 0)	row[i] /= sum;
	}
}

void Tuple::Register(string s){
	Dismantle(s, false);
	Updaterow();
}

#define Manhattan
//#define Euclidean
//#define cos 
//	calculate the distance of two tuple;
double Tuple::Distanceof(Tuple tup){
	vector<double> a = row;
	vector<double> b = tup.row;
	double dst = 0;
	#ifdef Manhattan
	for(int i=0; i<b.size(); i++){
		double av=a[i], bv=b[i];
		dst = dst + abs(bv-av);
	}
	return dst;
	#endif
	#ifdef Euclidean
	for(int i=0; i<b.size(); i++){
		double av=a[i], bv=b[i];
		dst = dst + (av-bv)*(av-bv);
	}
	return sqrt(dst);
	#endif 
	#ifdef cos
	double mtp = 0, square_alen = 0, square_blen = 0;
	for(int i=0; i<b.size(); i++){
		double av = a[i], bv = b[i];
		square_alen += av*av;
		square_blen += bv*bv;
		mtp += (av*bv);
	}
	dst = mtp/( sqrt(square_alen)*sqrt(square_blen) );
	#endif
}

//	check datas from tuples;
void Tuple::telescope(){
	for(int i=0; i<vca.size(); i++){
		cout << vca[i] << ' '; 
	}printf(",");
	cout << label << endl;
}
