#include<string>
#include<vector>
#include<iostream>
using namespace std;

#include"Tree.h"
#include"AnsStream.h"

//递归建树
static void generateTree(node&, const vector<vector<int>>&, const vector<int>&,
	int(*)(const vector<vector<int>>&, const vector<int>&));


static int getAns_(const node&, const vector<int>&);

node::node() {
	type = false;
	above = NULL;
}

Tree::Tree(const vector<vector<int>>& data, const vector<int>&flag,
	int(*func)(const vector<vector<int>>&, const vector<int>&)) {
	generateTree(root, data, flag, func);
}

static void generateTree(node&thisNode, const vector<vector<int>>&data, const vector<int>&flag,
	int(*func)(const vector<vector<int>>&, const vector<int>&)) {
	int select, length, len2, i, j, pointer, p;
	double pers;
	bool exist;
	vector<int>datas;
	//保存对应数据的所有行坐标
	vector<vector<int>>datasIndex;
	vector<vector<int>>thisData;
	vector<int>thisFlag;


	//判断终结树/递归
	//统计特征值中的最大值
	length = data.size();
	i = 0; j = 0;
	for (p = 0; p < length; p++) {
		if (flag[p] > 0)i++;
		else j++;
	}
	pers = double((i > j) ? i : j) / double(length);
	thisNode.ans = (i > j) ? 1 : -1;

	if (pers > persent_border) {
		//终结当前节点
		thisNode.type = true;
	}
	else {
		//获取选择的特征
		select = func(data, flag);
		datas.clear();
		//length = data.size();

		//找出包含的项→用于创建叶子节点
		for (i = 0; i < length; i++) {
			exist = 0;
			for (j = 0; j < datas.size(); j++) {
				if (datas[j] == data[i][select]) {
					datasIndex[j].push_back(i);
					exist = 1;
					break;
				}
			}
			if (!exist) {
				datasIndex.push_back(thisFlag);
				datasIndex[datasIndex.size() - 1].push_back(i);
				datas.push_back(data[i][select]);
			}
		}

		//创建子节点 并递归
		length = datas.size();
		for (i = 0; i < length; i++) {
			node newNode;
			newNode.dataIndex = select;
			newNode.data = datas[i];
			newNode.above = &thisNode;
			//为递归创建数据
			thisData.clear();
			thisFlag.clear();
			len2 = datasIndex[i].size();
			for (j = 0; j < len2; j++) {
				pointer = datasIndex[i][j];
				thisData.push_back(data[pointer]);
				thisFlag.push_back(flag[pointer]);
				//删除指定列的
				thisData[j].erase(thisData[j].begin()+select);
			}
			//递归
			generateTree(newNode, thisData, thisFlag, func);

			//保存子节点
			thisNode.below.push_back(newNode);
		}
	}
}

int Tree::getAns(const vector<int>&thisData) {
	return getAns_(root, thisData);
}
vector<int> Tree::getGroupAns(const vector<vector<int>>&thisData) {
	vector<int>thisAns;
	for (int i = 0; i < thisData.size(); i++) {
		thisAns.push_back(getAns(thisData[i]));
	}
	return thisAns;
}

static int getAns_(const node&thisNode, const vector<int>&thisData) {
	if (thisNode.type) {
		return thisNode.ans;
	}
	else {
		int thisData_ = thisData[thisNode.below[0].dataIndex];
		for (int i = 0; i < thisNode.below.size(); i++) {
			if (thisNode.below[i].data == thisData_)
				return getAns_(thisNode.below[i], thisData);
		}
	}
	//目标数据顺当前枝找不到对应的子节点
	return thisNode.ans;
}
//后剪枝
void Tree::cut(const vector<vector<int>>&thisData, const vector<int>&thisFlag) {
	cutNode(root, thisData, thisFlag);
}

void Tree::cutNode(node&thisNode, const vector<vector<int>>&thisData, const vector<int>&thisFlag) {
	if (thisNode.type) return;
	else {
		//先修改子节点
		int length = thisNode.below.size();
		for (int i = 0; i < length; i++) {
			cutNode(thisNode.below[i], thisData, thisFlag);
		}

		//修改自身
		//修改前
		vector<int>pre = getGroupAns(thisData);
		AnsStream preAns(pre);
		preAns.test(thisFlag, 0);
		double preAccuray = preAns.Point();
		//修改后
		thisNode.type = true;
		vector<int>post = getGroupAns(thisData);
		AnsStream postAns(post);
		postAns.test(thisFlag, 0);
		double postAccuray = postAns.Point();
		//最终觉得是否改变节点类型
		if (preAccuray > postAccuray)thisNode.type = false;
		else thisNode.below.clear();
	}
}