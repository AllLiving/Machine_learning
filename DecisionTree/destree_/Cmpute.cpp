#include <bits/stdc++.h>
#include "Cmpute.h"
using namespace std;

double entropy(vector<int> sequence){
	vector<int> v = sequence;// 为了少打字母，改名为v 
	// 对该序列中的不同的数字计数 
	map<int, int> cnt;
	for(int i=0; i<v.size(); i++)	cnt[v[i]]++;
	
	double entr = 0;
	// 计算每一种数值的熵； 
	for(map<int, int>::iterator it=cnt.begin(); it!=cnt.end(); it++){
		int cnt_attr = (int)(it->second);
		int whole_attr = v.size();
		double ratio = (double)cnt_attr/whole_attr;
		entr += -1 * ratio * log(ratio) / log(2.0);// 求和； 
	}
	// 返回 求得的熵 
	return entr;
}

vector<int> attr_filter(vector<int> attribute){
	vector<int> attr_sample;
	int attr_kind = 0;// 查询属性序列中有几种属性 
	for(int i=0; i<attribute.size(); i++){
		int crt_attr = attribute[i];
		vector<int>::iterator it
			= find(attr_sample.begin(), attr_sample.end(), crt_attr);
		// attr_sample储存各自不同的属性 
		if(it == attr_sample.end()){
			attr_kind++;
			attr_sample.push_back(crt_attr);
		}
	}
	return attr_sample;
}

double gini(vector<int> sequence){
	vector<int> seq = sequence;
	double all = seq.size();
	vector<int> attr_sample = attr_filter(seq);
	
	double sqrsum = 0;
	for(int i=0; i<attr_sample.size(); i++){
		int cnt = count(seq.begin(), seq.end(), attr_sample[i]);
		sqrsum = sqrsum + (cnt/all)*(cnt/all);
	}
	return (1-sqrsum);
}

double attr_entropy(vector<int> attribute, vector<int> label){
	
	vector<int> attr_sample = attr_filter(attribute);
	int attr_kind = attr_sample.size();
	double entr = 0;
//	 根据不同的属性将label分割为几段 ， 分别计算熵 
	for(int i=0; i<attr_kind; i++){
		int crt_attr = attr_sample[i];
		int attr_fit = 0;
		
		vector<int> toentpy; // 用于储存分割后的label序列 
		for(int k=0; k<attribute.size(); k++){
			int tst_attr = attribute[k];
			int crt_label = label[k];
			if(tst_attr == crt_attr){// 对当前属性分割 
				toentpy.push_back(crt_label);
				attr_fit++;
			}
		}
		
		double part_entropy = (double)attr_fit/attribute.size();
		entr += part_entropy*entropy(toentpy);
	}
	return entr;
} 

double infogain(vector<int> attribute, vector<int> label){
	vector<int> attr = attribute;
	double LabelEntropy = entropy(label);
//	printf("label's entropy=%lf\n", LabelEntropy);
	double AttrEntropy = attr_entropy(attr, label);
//	printf("attribute entropy=%lf\n", AttrEntropy);
	return (LabelEntropy - AttrEntropy);
}

double inforatio(vector<int> attribute, vector<int> label){
	vector<int> attr = attribute;
	double HeadEntropy = entropy(label);
	double TailEntropy = attr_entropy(attr, label);
	double AttrEntropy = entropy(attr);
	return ((HeadEntropy - TailEntropy)/AttrEntropy);
}

double syn_gini(vector<int> attribute, vector<int> label){
	vector<int> attr_sample = attr_filter(attribute);
	int attr_kind = attr_sample.size();
	double gn = 0;
	for(int i=0; i<attr_kind; i++){
		int crt_attr = attr_sample[i];
		
		vector<int> toentpy;
		for(int k=0; k<attribute.size(); k++){
			int tst_attr = attribute[k];
			int crt_label = label[k];
			if(tst_attr == crt_attr){
				toentpy.push_back(crt_label);
			}
		}
		
		gn += gini(toentpy);
	}
	return gn;
}

int forans(vector<int> v){
	int ans, max=0;
	map<int, int> cnt_lab;
	for(int lpin=0; lpin<v.size(); lpin++){
		int crt_lab = v[lpin];
		cnt_lab[crt_lab]++;
		if(cnt_lab[crt_lab] > max){
			max = crt_lab;
		}
	}
	return max; 
}

string tostring(int num){
	int v = num;
	string s;
	while(v/10){
		char c = (v%10) + '0';
		s += c;
		v /= 10;
	}
	char c = v + '0';
	s += c;
	string ans;
	for(int i=(s.size()-1); i>=0; i--)	ans += s[i];
	return ans;
}

int near_branch(int num, vector<int> branches){
//		brcs is short for branches;
	vector<int> brcs =  branches;
	for(int i=0; i<brcs.size(); i++){
		if(brcs[i] == num){
			return num;
		}
	}
	
	vector<int>::iterator it = max_element(brcs.begin(), brcs.end());
	int max_brc = *it;
	it = min_element(brcs.begin(), brcs.end());
	int min_brc = *it;
	if(num > max_brc){
		num = max_brc;
	}else if(num < min_brc){
		num = min_brc;
	}else{	 
		int small, big;
		vector<int> v = brcs;
		sort(v.begin(), v.end());
		for(int i=0; i<v.size(); i++){
			if(v[i] > num){
				small = v[i-1];
				big = v[i];
				break;
			} 
		}
		if(num < (small+big)/2){
			return small;
		}else{
			return big;
		}
	}
	return num;
}

