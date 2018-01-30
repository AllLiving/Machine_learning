#include <bits/stdc++.h>
using namespace std;

// ����һ�����е��أ� 
double entropy(vector<int> sequence){
	vector<int> v = sequence;// Ϊ���ٴ���ĸ������Ϊv 
	// �Ը������еĲ�ͬ�����ּ��� 
	map<int, int> cnt;
	for(int i=0; i<v.size(); i++)	cnt[v[i]]++;
	
	double entr = 0;
	// ����ÿһ����ֵ���أ� 
	for(map<int, int>::iterator it=cnt.begin(); it!=cnt.end(); it++){
		int cnt_attr = (int)(it->second);
		int whole_attr = v.size();
		double ratio = (double)cnt_attr/whole_attr;
		entr += -1 * ratio * log(ratio) / log(2.0);// ��ͣ� 
	}
	// ���� ��õ��� 
	return entr;
}

// ��������������Ƶ�����£���label���е��أ� 
double attr_entropy(vector<int> attribute, vector<int> label){
	vector<int> attr_sample;
	int attr_kind = 0;// ��ѯ�����������м������� 
	for(int i=0; i<attribute.size(); i++){
		int crt_attr = attribute[i];
		vector<int>::iterator it
			= find(attr_sample.begin(), attr_sample.end(), crt_attr);
		// attr_sample������Բ�ͬ������ 
		if(it == attr_sample.end()){
			attr_kind++;
			attr_sample.push_back(crt_attr);
		}
	}
	
	double entr = 0;
//	 ���ݲ�ͬ�����Խ�label�ָ�Ϊ���� �� �ֱ������ 
	for(int i=0; i<attr_kind; i++){
		int crt_attr = attr_sample[i];
		
		vector<int> toentpy; // ���ڴ���ָ���label���� 
		for(int k=0; k<attribute.size(); k++){
			int tst_attr = attribute[k];
			int crt_label = label[k];
			if(tst_attr == crt_attr){// �Ե�ǰ���Էָ� 
				toentpy.push_back(crt_label);
			}
		}
		
		// ����õ������ͣ� 
		entr += entropy(toentpy);
	}
	return entr;
} 


int main(){

/**				С���ݼ�����				**/
//	�����������ԣ��Ա��������㣻 

	vector<int> attr1, attr2;
	int data[] = {1, 2, 2, 2, 1};
	// ����1,�� 1 2 2 2 1 
	for(int i=0; i<5; i++)
		attr1.push_back(data[i]);
	// ����2�� 1 2 2 2 5 
	for(int i=0; i<4; i++)
		attr2.push_back(data[i]);
	attr2.push_back(5);
	
//	����label���Ա����������أ� 
	int forlabel[] = {1, 1, 0, 0, 0};
	// label�� 1 1 0 0 0 
	vector<int> label;
	for(int i=0; i<5; i++){
		label.push_back(forlabel[i]);
	}
	
//	�����������Զ�Ӧ����Ϣ�أ� ʹ����Ϣ�ظ�С�ģ� 
	double entropy1 = attr_entropy(attr1, label);
	double entropy2 = attr_entropy(attr2, label);
	if(entropy1 < entropy2){
		printf("we choose attribute 1 as our root-attribute.\n");
	}else{
		printf("we choose attribute 2 as our root-attribute.\n");
	}
/**				С���ݼ�����				**/
	return 0;
} 













