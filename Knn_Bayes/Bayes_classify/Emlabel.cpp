#include "Emlabel.h"
#include <bits/stdc++.h>
using namespace std;

//	repetitive;
vector<string> joylabel_;
vector<string> sadlabel_;
vector<string> disgustlabel_;
vector<string> surplabel_;
vector<string> angerlabel_;
vector<string> fearlabel_;
//	non-repetitive;
vector<string> joylabel;
vector<string> sadlabel;
vector<string> disgustlabel;
vector<string> surplabel;
vector<string> angerlabel;
vector<string> fearlabel;
int joyvocnt = 0;
int sadvocnt = 0;
int disgustvocnt = 0;
int surprisevocnt = 0;
int angervocnt = 0;
int fearvocnt = 0;

int get_size(string emotion, bool repeat){
	if(emotion == "joy"){
		if(repeat)	return joylabel_.size();
		else	return joylabel.size();
	}else if(emotion == "sad"){
		if(repeat)	return	sadlabel_.size();
		else	return sadlabel.size();
	}else if(emotion == "disgust"){
		if(repeat)	return	disgustlabel_.size();
		else	return disgustlabel.size();
	}else if(emotion == "anger"){
		if(repeat)	return	angerlabel_.size();
		else	return angerlabel.size();
	}else if(emotion == "surprise"){
		if(repeat)	return	surplabel_.size();
		else	return surplabel.size();
	}else if(emotion == "fear"){
		if(repeat)	return	fearlabel_.size();
		else	return fearlabel.size();
	}
}

int count_words(string emotion, string word){
	if(emotion == "joy"){
		if(joylabel_.size() == 0)	return 0;
		int cnt = count(joylabel_.begin(), joylabel_.end(), word);
		return cnt;
	}else if(emotion == "sad"){
		if(sadlabel_.size() == 0)	return 0;
		int cnt = count(sadlabel_.begin(), sadlabel_.end(), word);
		return cnt;
	}else if(emotion == "disgust"){
		if(disgustlabel_.size() == 0)	return 0;
		int cnt = count(disgustlabel_.begin(), disgustlabel_.end(), word);
		return cnt;
	}else if(emotion == "anger"){
		if(angerlabel_.size() == 0)	return 0;
		int cnt = count(angerlabel_.begin(), angerlabel_.end(), word);
		return cnt;
	}else if(emotion == "surprise"){
		if(surplabel_.size() == 0)	return 0;
		int cnt = count(surplabel_.begin(), surplabel_.end(), word);
		return cnt;
	}else if(emotion == "fear"){
		if(fearlabel_.size() == 0)	return 0;
		int cnt = count(fearlabel_.begin(), fearlabel_.end(), word);
		return cnt;
	}
}
vector<string> Read_label(string fname){
	fstream fin(fname, ios::in);
	char c;
	bool Is_label = false;
	vector<string> labelbase;
	while((c=fin.get()) != '\n');
	while((c=fin.get()) != EOF){
		if(c == ','||c == '\n')	Is_label = !Is_label;
		if(Is_label){
			string label;
			fin >> label;
//			cout << "label:" << label << endl;
			labelbase.push_back(label);
		}
	}
	return labelbase;
}

double Ratio(vector<string> va, vector<string> vb){
	if(va.size() != vb.size()){
		printf("va size=%d"); 	cout << va.size() << endl;
		printf("vb size=%d");	cout << vb.size() << endl;
		printf("[Emlabel.cpp/Radio]va's size != vb's size.\n");
	}
	double size = va.size(), cnt = 0;
	for(int i=0; i<size; i++){
		if(va[i] == vb[i])	cnt++;
		else{
//			cout << "index=" << i << endl;
//			cout << "va:" << va[i] << endl;
//			cout << "vb:" << vb[i] << endl;
		}
	}
	printf("cnt=%lf\n", cnt);
	printf("size=%lf\n", size);
	return ((double)cnt/size);
}

void fillemlabel(string emotion, vector<string> LinkEmotionVocabularyBase){
	vector<string> lv = LinkEmotionVocabularyBase;
	if(emotion == "joy"){
		for(int i=0; i<lv.size(); i++){
//			joyvocnt++;
			joylabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(joylabel.begin(), joylabel.end(), lv[i]);
			if(it == joylabel.end())	joylabel.push_back(lv[i]);
		}
	}else if(emotion == "sad"){
		for(int i=0; i<lv.size(); i++){
//			sadvocnt++;
			sadlabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(sadlabel.begin(), sadlabel.end(), lv[i]);
			if(it == sadlabel.end())	sadlabel.push_back(lv[i]);
		}
	}else if(emotion == "disgust"){
		for(int i=0; i<lv.size(); i++){
//			disgustvocnt++;
			disgustlabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(disgustlabel.begin(), disgustlabel.end(), lv[i]);
			if(it == disgustlabel.end())	disgustlabel.push_back(lv[i]);
		}
	}else if(emotion == "surprise"){
		for(int i=0; i<lv.size(); i++){
//			surprisevocnt++;
			surplabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(surplabel.begin(), surplabel.end(), lv[i]);
			if(it == surplabel.end())	surplabel.push_back(lv[i]);
		}
	}else if(emotion == "anger"){
		for(int i=0; i<lv.size(); i++){
//			angervocnt++;
			angerlabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(angerlabel.begin(), angerlabel.end(), lv[i]);
			if(it == angerlabel.end())	angerlabel.push_back(lv[i]);
		}
	}else if(emotion == "fear"){
		for(int i=0; i<lv.size(); i++){
//			fearvocnt++;
			fearlabel_.push_back(lv[i]);
			vector<string>::iterator it = 
				find(fearlabel.begin(), fearlabel.end(), lv[i]);
			if(it == fearlabel.end())	fearlabel.push_back(lv[i]);
		}
	}
	return;
}
