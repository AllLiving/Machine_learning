#include<vector>
#include<iostream>
using namespace std;

#include"lib\Reader.h"
#include"lib\ID3.h"
#include"lib\C4.5.h"
#include"lib\Gini.h"
#include"lib\Tree.h"
#include"lib\Divider.h"
#include"lib\AnsStream.h"

int main() {
	//分割训练集与验证集用
	//Divider("origin.csv");

	Reader trainReader("train.csv");
	Reader valiReader("validation.csv");

	//使用ID3生成树
	Tree treeID3(trainReader.data, trainReader.flag, ID3);
	cout << "ID3剪枝前:\n";
	AnsStream ansStreamID3_(treeID3.getGroupAns(valiReader.data));
	ansStreamID3_.test(valiReader.flag);
	cout << "ID3剪枝后:\n";
	treeID3.cut(valiReader.data, valiReader.flag);
	AnsStream ansStreamID3(treeID3.getGroupAns(valiReader.data));
	ansStreamID3.test(valiReader.flag);
	ansStreamID3.writeFile("ID3.csv");

	//使用C4.5生成树
	Tree treeC45(trainReader.data, trainReader.flag, C45);
	cout << "C4.5剪枝前:\n";
	AnsStream ansStreamC45_(treeC45.getGroupAns(valiReader.data));
	ansStreamC45_.test(valiReader.flag);
	cout << "C4.5剪枝后:\n";
	treeC45.cut(trainReader.data, trainReader.flag);
	AnsStream ansStreamC45(treeC45.getGroupAns(valiReader.data));
	ansStreamC45.test(valiReader.flag);
	ansStreamC45.writeFile("C45.csv");
	
	//使用Gini指数生成树
	Tree treeGini(trainReader.data, trainReader.flag, Gini);
	cout << "Gini剪枝前:\n";
	AnsStream ansStreamGini_(treeGini.getGroupAns(valiReader.data));
	ansStreamGini_.test(valiReader.flag);
	cout << "Gini剪枝后:\n";
	treeGini.cut(trainReader.data, trainReader.flag);
	AnsStream ansStreamGini(treeGini.getGroupAns(valiReader.data));
	ansStreamGini.test(valiReader.flag);
	ansStreamGini.writeFile("Gini.csv");

	system("pause");
	return 0;
}
