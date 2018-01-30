#include <iostream>
#include <bits/stdc++.h> 
#include "Unused.h"
#include "Root.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define test
int main(int argc, char** argv) {
	
	train("YStrain1.csv");
	Root *node = new Root();
	printf("[main]Building...\n");
	node->build(ATTRSET, LABEL);
	printf("[main]Finish building.\n\n\n");
	if(node->leafans == true){
		printf("only one node!\n");
		exit(0);
	}
	
	#ifndef test
	int attrs_data[] = {42, 1, 3, 2, 1, 1, 2, 3, 0};
	vector<int> attrs;
	for(int i=0; i<9; i++){
		attrs.push_back(attrs_data[i]);
	}
	
	int ans = node->getans(attrs);
	printf("We've get the ans:%d\n", ans);
	#endif
	
	#ifdef test
	valid("YStest1.csv");
//	printf("valid_attr-size=%d\n", V_attrs.size());
	vector<int> output;
	for(int vpin=0; vpin<V_attrs.size(); vpin++){
		vector<int> crt_attr = V_attrs[vpin];
		printf("[main]/fortest:dealing with attrs:");
		for(int i=0; i<crt_attr.size(); i++){
			cout << crt_attr[i] << ' ';
		}cout << endl;
		int ans = node->getans(crt_attr);
		printf("[main]/fortest:ans=%d\n", ans);
		output.push_back(ans);
		for(int i=0; i<45; i++)
		printf("-");
		printf("\n");
//		printf("We get %dth ans:%d\n", vpin, ans);
//		system("pause");
	}

	/*
	fstream fout("ans.csv", ios::out);
	int atrs = V_attrs.size();
	int oups = output.size();
	for(int opin=0; opin<oups; opin++){
		int forout = output[opin];
		fout << forout << ',';
		fout << '\n';
	}
	
	printf("Calculationg your ratio...\n");
	if(V_label.size() != output.size()){
		printf("Data for outputing has wrong count.\n");
		exit(0);
	}
	int cnt=0;
	vector<int> error_info;
	for(int i=0; i<V_label.size(); i++){
		if(V_label[i] == output[i]){
			cnt++;
		}else{
			error_info.push_back(i);
		}
	}
	
	printf("\n\nShoot:%d\n", cnt);
	printf("All:%d\n", output.size());
	printf("Ratio:%lf%\n", 100*(double)cnt/output.size());
	
//	printf("[Main]:error information:\n");
//	for(int i=0; i<error_info.size(); i++){
//		printf("\t%dth wrong.\n", error_info[i]);
//	}*/
	#endif
	
	return 0;
}
