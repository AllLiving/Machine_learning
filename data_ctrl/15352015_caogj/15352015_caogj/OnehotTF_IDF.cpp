#include <iostream>  
#include <string>  
#include <vector>  
#include <bits/stdc++.h>
using namespace std;
//#define one_hot
//#define tf 
#define TFidf

vector<string> vcts;
vector<string> vctv;

//	split the sentence;
vector<string> split_sentence(string s_reg, bool same){
	stringstream sm;
	sm << s_reg;
	
	string tmp;
	vector<string> vctvSame;
	while(( sm.good() )&&( sm >> tmp )){
		bool ext_num = false;
		for(int i=0; i<tmp.length(); i++){
			if(isdigit(tmp[i]) == 1){
				ext_num = true;
				break;
			}
		}
		if(ext_num == false){
			if(same){
				vctvSame.push_back(tmp);
			}else{
				vector<string>::iterator it 
					= find(vctv.begin(), vctv.end(), tmp);
				if(it == vctv.end())
					vctv.push_back(tmp);
			}
		}
	}
	
//	char *stxt = &s_reg[0];
////	all of the milestones;
//	const char *d="\t1234567890:\n ";
//	char *vocabulary;
//	vocabulary = strtok(stxt, d);
//	vector<string> vctvSame;
////	continue the spliting process until ...
//	while(vocabulary){
////		vectorSame designed for calculating TF matrix; 
//		if(same)	vctvSame.push_back(vocabulary);
//		else{
////			To make sure all elements are diff;
//			vector<string>::iterator it 
//				= find(vctv.begin(), vctv.end(), vocabulary);
//			if(it == vctv.end())
//				vctv.push_back(vocabulary);
//		}
////		With Null, won't change sentence to split;
//		vocabulary = strtok(NULL, d);
//	}
	
	return vctvSame;
}

//calculate weight with vector containing the same elements;
map<string, double> Cwgt(vector<string> v, bool IDF) {

//	sum 为出现的词汇总数； 
	int sum = 0;
//	为了实现 “词汇 => 数目”的索引，使用map结构； 
	map<string, int> m;
	for (int i = 0; i < v.size(); i++) {
		m[v[i]] += 1;
		sum += 1;
	}
//	实现“词汇 => 归一化系数”的索引； 
	map<string, double> mwgt;
	for (int i = 0; i < v.size(); i++) {
		string s = v[i];
		mwgt[s] = (double)m[s] / sum;
	}

	return mwgt;
}

int main()  
{  
	fstream f("text.txt", ios::in);
	string s_reg, s_tmp;
	char c;
	while((c=f.get()) != EOF){
//		prepare sentences from the paragraph; 
		s_reg += c;
		s_tmp += c;
//		split the parageaph by milestones;
		if(c == '\n'){
			vcts.push_back(s_tmp);
			s_tmp = "";
		}
	}
	
	split_sentence(s_reg, false);
	
//	construct the matrix
	#ifdef one_hot
	printf("now create matrix.\n");
	ofstream fout("onehot.txt");
	for(int stc=0; stc<vcts.size(); stc++){
		string s = vcts[stc];
		for(int voc=0; voc<vctv.size(); voc++){
			bool ans = ( s.find(vctv[voc], 0) < s.size() );
			fout << ans;
		}
		fout << endl;
	}
	#endif
	
//	capacity of sentences is vcts;
//	capacity of vocabulary is vctv;
	#ifdef tf
	printf("Create matrix.\n");
	ofstream fout("tf.txt");
	for(int stc=0; stc<vcts.size(); stc++){
		string s = vcts[stc];
//		calculate the weight;
		vector<string> vctvSame = split_sentence(s, true);
		map<string, double> m = Cwgt(vctvSame, false);
		
		for(int voc=0; voc<vctv.size(); voc++){
			if(s.find(vctv[voc], 0) >= s.size())	fout << 0 << ' ';
			else{
				fout << m[vctv[voc]] << ' ';
			}
		}
		fout << endl;
	}
	#endif
	
	#ifdef TFidf
	printf("Create matrix.\n");
	ofstream fout("tfidf.txt");
	map<string, int> relateFiles;
	for(int voc=0; voc<vctv.size(); voc++){
		for(int stc=0; stc<vcts.size(); stc++){
			bool ans = false;
			string s = vcts[stc];
			ans = ( s.find(vctv[voc], 0) < s.size() );
			if(ans)	relateFiles[vctv[voc]]++;
		}
	}
	
	for(int stc=0; stc<vcts.size(); stc++){
		string s = vcts[stc];
//		calculate the weight;
		vector<string> vctvSame = split_sentence(s, true);
		map<string, double> m = Cwgt(vctvSame, false);
		
		for(int voc=0; voc<vctv.size(); voc++){
			if(s.find(vctv[voc], 0) >= s.size())	fout << 0 << ' ';
			else{
				int num = vcts.size();
				double fan = m[vctv[voc]] * log( ((double)num / (1+relateFiles[vctv[voc]])) );
				if(fan)		fout << fan << ' ';
				else fout << 0 << ' ';
			}
		}
		fout << endl;
	}
	#endif
	
    return 0;  
}  
