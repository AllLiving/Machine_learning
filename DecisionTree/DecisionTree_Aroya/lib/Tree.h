#ifndef AROYA_DECISION_TREE
#define AROYA_DECISION_TREE

#define persent_border 0.9

struct node {
	bool type;//true→ans，false→data
	int dataIndex;//记录是第几列的数据
	int data;//记录数据的类型
	int ans;//若得到结果则在这里记录结果类型
	node *above;//上层枝干
	vector<node>below;
	node();
};

class Tree {
private:
	node root;
	void cutNode(node&, const vector<vector<int>>&, const vector<int>&);
public:
	//直接创建树,传入所有数据、flag数据、判别函数
	Tree(const vector<vector<int>>&, const vector<int>&,
		int(*)(const vector<vector<int>>&, const vector<int>&));
	//返回ans
	int getAns(const vector<int>&);
	vector<int> getGroupAns(const vector<vector<int>>&);

	//后剪枝
	void cut(const vector<vector<int>>&,const vector<int>&);
	
};

#endif