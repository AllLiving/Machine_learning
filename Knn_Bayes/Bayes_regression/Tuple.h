#include <bits/stdc++.h>
using namespace std;

class Tuple{
public:
//	For updating;
	void Collectvoc(string s, bool fix_base);
	void Updatebaserow();
	void Register(string s);
	double Distanceof(Tuple tuple);
	void SetEmotionbar(vector<double> emotionbar);
	void taste();
//	For checking;
	void visit_emotionbar();
	void visit_vocaset();
	void visit_baserow(){
		for(int i=0; i<baserow.size(); i++){
			cout << baserow[i] << ' ';
		}cout << endl;
	}
	void visit_vocarow(){
		for(int i=0; i<vocarow.size(); i++){
			cout << vocarow[i] << ' ';
		}cout << endl;
	}
	
	vector<string> voca;
	vector<double> baserow;
	vector<double> vocarow;
private:
	vector<double> emotionbar;
};

extern vector<string> vocbase;
extern vector<Tuple> Tuplebase;
extern vector<string> Validbase;
extern vector<double> output;
extern void Visit_vocbase();
extern void train(string fname);
extern void valid(string fname);
