#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

#include"ID3.h"

//返回一个数在vector<int>中的index
static int inline findInVector(const vector<int>&, const int&);


//返回选择的列的index
int ID3(const vector<vector<int>>& data, const vector<int>& flag) {
	//先统计 列：特征数； 行：样例数
	const int columns = data[0].size();
	const int rows = data.size();
	
	const int zero = 0;
	vector<int>value;
	vector<int>count;
	vector<int>positive;
	vector<int>negative;
	vector<double>entropy;
	int index;
	double thisEntropy;
	//计算所有列
	for (int i = 0; i < columns; i++) {
		//初始化
		value.clear();
		count.clear();
		positive.clear();
		negative.clear();
		thisEntropy = 0;
		//计数
		for (int j = 0; j < rows; j++) {
			//查找离散值值
			index = findInVector(value, data[j][i]);
			//没有则创建
			if (index < 0) {
				value.push_back(data[j][i]);
				count.push_back(zero);
				positive.push_back(zero);
				negative.push_back(zero);
				index = value.size() - 1;
			}
			//离散值计数
			count[index]++;
			//离散值对应状态统计
			if (flag[j] > 0)positive[index]++;
			else negative[index]++;
		}
		//计算条件熵
		index = value.size();
		for (int j = 0; j < index; j++) {
			/*H(D|A) = sum all A
				P(A=a)*
				H(D|A=a)
				*/
			thisEntropy += (
				double(count[j]) / double(rows)*
				(
					- double(positive[j]) / double(count[j])*log2((double(positive[j])+0.01) / double(count[j]))
					- double(negative[j]) / double(count[j])*log2((double(negative[j])+0.01) / double(count[j]))
				)
			);//+0.01 防止log2(0/count)导致结果出现nan
		}
		entropy.push_back(thisEntropy);
	}
	//所有条件熵计算完毕，寻找条件熵最小，即选择后信息增益最大
	double min = entropy[0];
	index = 0;
	for (int i = 1; i < columns; i++) {
		if (entropy[i] < min) {
			index = i;
			min = entropy[i];
		}
	}
	return index;
}

static int inline findInVector(const vector<int>& thisVector, const int& num) {
	const int border = thisVector.size();
	for (int i = 0; i < border; i++) {
		if (thisVector[i] == num)return i;
	}
	return -1;
}