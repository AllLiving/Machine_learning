#include "tuple.h"
using namespace std;

vector<string> vocbase;
vector<Tuple> Tuplebase;
vector<string> Validbase;
vector<double> output;

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
inline void Tuple::Updatebaserow(){
	for(int i=0; i<vocbase.size(); i++){
		double cnt = 0;
		for(int vpin=0; vpin<voca.size(); vpin++){
			if(voca[vpin] == vocbase[i])	cnt++;
		}
		baserow.push_back(cnt);
	}
	for(int rpin=0; rpin<baserow.size(); rpin++){
		if(baserow[rpin] != 0){
			baserow[rpin] /= voca.size();
			vocarow.push_back(baserow[rpin]);
		} 
	}
}

void Tuple::Register(string s){
	Collectvoc(s, false);
	Updatebaserow();
}

#define Manhattan
//#define Euclidean

//	calculate the distance of two tuple;
double Tuple::Distanceof(Tuple tup){
	vector<double> a = baserow;
	vector<double> b = tup.baserow;
	if(( a.size() != b.size() )||( a.size() == 0)||(b.size() == 0)){
		printf("one of tuples has non-valued baserow.\n");
		exit(0);
	}
	double dst = 0;
	#ifdef Manhattan
	for(int i=0; i<b.size(); i++){
		dst = dst + abs(a[i]-b[i]);
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
}
 
void Tuple::SetEmotionbar(vector<double> emotionbar){
	this->emotionbar = emotionbar;
}
 
//	[Tuple]	feelbar + distance	=>	feels;
//#define Laplace
#define Tiny 0.0000000000000000001
#define tiny
//#define Better
void Tuple::taste(){
	vector<double> emcapsule;
	
	double emoj[6] = {0, 0, 0, 0, 0, 0};
	for(int tpin=0; tpin<Tuplebase.size(); tpin++){
		Tuple crt_tp = Tuplebase[tpin];
		if(Distanceof(crt_tp) == 0){
			for(int i=0; i<6; i++){
				emoj[i] = crt_tp.emotionbar[i];
			}
			break;
		}else{
//			printf("crt_em = crt_tp.emtionbar[empin] X MultipleResult\n");
//			printf("[Taste]:We are calculating the Result...\n");
			vector<double> vwgts;// vocabulary weight set;
			for(int vpin=0; vpin<voca.size(); vpin++){
				double vwgt=0;
				// shall update emotionbar;
				for(int tvpin=0; tvpin<crt_tp.voca.size(); tvpin++){
					if(voca[vpin] == crt_tp.voca[tvpin]){
						vwgt = crt_tp.vocarow[tvpin];
						break;
					}
				}
				vwgts.push_back(vwgt);
			}
			double vwgtsum = 0;// for bayes;
			for(int vwpin=0; vwpin<vwgts.size(); vwpin++)	vwgtsum += vwgts[vwpin];
			for(int vwpin=0; vwpin<vwgts.size(); vwpin++){
				double iniwgt = vwgts[vwpin];
				vwgts[vwpin] = iniwgt;
				#ifdef tiny
				if(iniwgt != 0){
					vwgts[vwpin] = iniwgt;
				}else{
					vwgts[vwpin] = pow(1.001, iniwgt) - 1 + Tiny;
				}
				#endif
				#ifdef Laplace
				vwgts[vwpin] = (iniwgt+1)/(vwgtsum+vwgts.size());
				#endif
			}
			
			double vwmultp=1; // for bayes;
			for(int vwpin=0; vwpin<vwgts.size(); vwpin++)
			{
				vwmultp *= vwgts[vwpin];
			}
			
//			update six emtions;
			string emset[]={"anger", "disgust", "fear", "joy", "sad", "surprise"};
			for(int empin=0; empin<6; empin++){
				double crt_em = -1;
				if(crt_tp.emotionbar[empin] == 0){
					crt_em = 0;
				}else{
					crt_em = vwmultp * crt_tp.emotionbar[empin];
				}
				emoj[empin] += (10000*crt_em);
//				cout << emset[empin] << ':' << crt_tp.emotionbar[empin] << endl;
//				emoj[empin] = emoj[empin] + (int)(100000*crt_em);
			}
		}
	}
	
	double sum = 0; 
	for(int i=0; i<6; i++){
		sum += emoj[i];
	}
	for(int i=0; i<6; i++){
		double hotel_v = emoj[i];
		hotel_v = hotel_v/sum;
		if(hotel_v < 1000){
			int scissors;
			hotel_v *= 10000;
			scissors = hotel_v;
			hotel_v = 0.0001 * scissors;
		}
		emoj[i] = hotel_v;
		emcapsule.push_back(emoj[i]);
	}
	
//	for(int i=0; i<emcapsule.size(); i++)	output.push_back(emcapsule[i]);
	SetEmotionbar(emcapsule);
	for(int i=0; i<emotionbar.size(); i++){
		output.push_back(emotionbar[i]);
	}
//	visit_emotionbar();
}

void Tuple::visit_emotionbar(){
	for(int i=0; i<emotionbar.size(); i++){
		cout << emotionbar[i] << ' ';
	}cout << endl;
}

//	check datas from tuples;
void Tuple::visit_vocaset(){
	for(int i=0; i<voca.size(); i++){
		cout << voca[i] << ' '; 
	}printf("\n");
}
