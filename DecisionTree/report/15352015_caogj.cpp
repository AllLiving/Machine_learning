#include <bits/stdc++.h>
using namespace std;

// 计算一个序列的熵； 
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

// 计算给定条件限制的情况下，该label序列的熵； 
double attr_entropy(vector<int> attribute, vector<int> label){
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
	
	double entr = 0;
//	 根据不同的属性将label分割为几段 ， 分别计算熵 
	for(int i=0; i<attr_kind; i++){
		int crt_attr = attr_sample[i];
		
		vector<int> toentpy; // 用于储存分割后的label序列 
		for(int k=0; k<attribute.size(); k++){
			int tst_attr = attribute[k];
			int crt_label = label[k];
			if(tst_attr == crt_attr){// 对当前属性分割 
				toentpy.push_back(crt_label);
			}
		}
		
		// 对求得的熵作和； 
		entr += entropy(toentpy);
	}
	return entr;
} 


int main(){

/**				小数据集测试				**/
//	设置两种属性，以备后续计算； 

	vector<int> attr1, attr2;
	int data[] = {1, 2, 2, 2, 1};
	// 属性1,： 1 2 2 2 1 
	for(int i=0; i<5; i++)
		attr1.push_back(data[i]);
	// 属性2： 1 2 2 2 5 
	for(int i=0; i<4; i++)
		attr2.push_back(data[i]);
	attr2.push_back(5);
	
//	设置label，以备后续计算熵； 
	int forlabel[] = {1, 1, 0, 0, 0};
	// label： 1 1 0 0 0 
	vector<int> label;
	for(int i=0; i<5; i++){
		label.push_back(forlabel[i]);
	}
	
//	计算两种属性对应的信息熵， 使用信息熵更小的； 
	double entropy1 = attr_entropy(attr1, label);
	double entropy2 = attr_entropy(attr2, label);
	if(entropy1 < entropy2){
		printf("we choose attribute 1 as our root-attribute.\n");
	}else{
		printf("we choose attribute 2 as our root-attribute.\n");
	}
/**				小数据集测试				**/
	return 0;
} 













