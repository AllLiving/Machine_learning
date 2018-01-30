#include<vector>
#include<cmath>
using namespace std;
#include"Gini.h"

//返回一个数在vector<int>中的index
static int inline findInVector(const vector<int>&, const int&);

int Gini(const vector<vector<int>>& data, const vector<int>& flag) {
	//先统计 列：特征数； 行：样例数
	const int columns = data[0].size();
	const int rows = data.size();

	const int zero = 0;
	vector<int>value;
	vector<int>count;
	vector<int>positive;
	vector<int>negative;
	vector<double>gini;
	int index;
	double thisGini;
	//计算所有列
	for (int i = 0; i < columns; i++) {
		//初始化
		value.clear();
		count.clear();
		positive.clear();
		negative.clear();
		thisGini = 0;
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

		//计算Gini指数
		index = value.size();
		for (int j = 0; j < index; j++) {
			/*H(D|A) = sum all
			出现概率*(
			1 - P(True|A)^2 - P(False|A)^2
			)*/
			thisGini += (
				double(count[j]) / double(rows)*
				(
					1.0 - pow(double(positive[j]) / double(count[j]), 2)
					- pow(double(negative[j]) / double(count[j]), 2)
				));
		}
		gini.push_back(thisGini);
	}
	//所有条件熵计算完毕，寻找条件熵最小，即选择后信息增益最大
	double min = gini[0];
	index = 0;
	for (int i = 1; i < columns; i++) {
		if (gini[i] < min) {
			index = i;
			min = gini[i];
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