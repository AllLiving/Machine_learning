#include <iostream>
#include <bits/stdc++.h> 
#include "Unused.h"
#include "Root.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define test
int main(int argc, char** argv) {
	
	train("train.csv");
	Root *node = new Root();
	printf("[main]Building...\n");
	node->build(ATTRSET, LABEL);
	printf("[main]Finish building.\n");
	if(node->leafans == true){
		printf("only one node!\n");
	}
	exit(0);
	
	#ifndef test
//	int attrs_data[] = {32, 0, 1, 6, 0, 1, 1, 2, 0};
	int attrs_data[] = {32,2,3,5,0,1,2,3,0};
	vector<int> attrs;
	for(int i=0; i<9; i++){
		attrs.push_back(attrs_data[i]);
	}
	
	int ans = node->getans(attrs);
	printf("We've get the ans:%d\n", ans);
	#endif
	
	#ifdef test
	valid("test.csv");
	printf("valid_attr-size=%d\n", V_attrs.size());
	vector<int> output;
	for(int vpin=0; vpin<V_attrs.size(); vpin++){
		vector<int> crt_attr = V_attrs[vpin];
		int ans = node->getans(crt_attr);
		output.push_back(ans);
	}
	
	printf("[main]:Streamnig to file...\n");
	fstream fout("ans.txt", ios::out);
	int atrs = V_attrs.size();
	int oups = output.size();
	for(int opin=0; opin<oups; opin++){
		int forout = output[opin];
		printf("%d\n", forout);
		if(forout == 1){
			fout << 1;
			fout << '\n';
		}else if(forout == -1){
			fout << -1;
			fout << '\n';
		}else{
			system("pause");
		}
	}
	
	printf("valid lines=%d\n", V_label.size());
	printf("output lines=%d\n", output.size());
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
//	}
	#endif
	
	return 0;
}
