#include <bits/stdc++.h>
#include "Unused.h"

using namespace std;

vector<vector<int>> ATTRSET;
vector<int> LABEL;
vector<vector<int>> V_attrs;
vector<int> V_label;

void forset(vector<vector<int>> set){
	int size = set.size();
	for(int i=0; i<size; i++){
		vector<int> attrset = set[i];
		for(int a=0; a<attrset.size(); a++){
			cout << setw(2) << attrset[a] << ' ';
		}cout << endl;
	}
}

void forlabel(vector<int> label){
	for(int i=0; i<label.size(); i++){
		cout << setw(2) << label[i] << ' ';
	}cout<<endl;
}

void train(string fname){
	char c;
	bool onlycheckinthefirstline = false;
	int num_attr = 0, lines = 0;
	fstream ftry(fname, ios::in);
	while((c=ftry.get()) != EOF){
//		cout << c;
		if((c == ',')&&(onlycheckinthefirstline == false))
			num_attr++;
		else if(c == '\n'){
			lines++;
			onlycheckinthefirstline = true;
		}
	}
	printf("train num_attr=%d\n", num_attr);
	printf("train lines=%d\n", lines);
	
	
	
	fstream f(fname, ios::in);
	
	printf("[train]:Initialize the attr_set...\n");
	for(int i=0; i<num_attr; i++){
		double attr; 		f >> attr;
		char nod; 		f >> nod;
		if((nod != ',')&&(nod != '\n'))
		{
			printf("maybe format wrong.\n");
		}
		vector<int> attr_set;
		attr_set.push_back(attr);
		ATTRSET.push_back(attr_set);
	}
	int lab; 		f >> lab;
	LABEL.push_back(lab);
	printf("[train]:Finish Initialization.\n");
	
	for(int l=1; l<lines; l++){
		for(int i=0; i<num_attr; i++){
			double attr;		f >> attr;
			char nod; 		f >> nod;
			if((nod != ',')&&(nod != '\n'))
			{
				printf("[train]:maybe format wrong.\n");
			}
			ATTRSET[i].push_back(attr);
		}
		int lab; 		f >> lab;
		LABEL.push_back(lab);
	}
	
	printf("[train]:finish train.\n");
	
//	forset(ATTRSET);
}

void valid(string fname){
	char c;
	bool onlycheckinthefirstline = false;
	int num_attr = 0, lines = 0;
	fstream ftry(fname, ios::in);
	while((c=ftry.get()) != EOF){
//		cout << c;
		if((c == ',')&&(onlycheckinthefirstline == false))
			num_attr++;
		else if(c == '\n'){
			lines++;
			onlycheckinthefirstline = true;
		}
	}
//	printf("num_attr=%d\n", num_attr);
//	printf("lines=%d\n", lines);
	
	
	fstream f(fname, ios::in);
	
	for(int l=0; l<lines; l++){
		vector<int> crt_set;
		for(int atpin=0; atpin<num_attr; atpin++){
			int attr;	f >> attr;
//			cout << attr << ' ';
			char c; 	f >> c;
//			cout << c <<  ' ';
			if(c != ','&&c != '\n'){
				printf("[valid]:valid maybe format wrong:");
				cout << c << endl;
				system("pause");
			}
			crt_set.push_back(attr);
		}
		V_attrs.push_back(crt_set);
		char lab;		f >> lab;
//		int lab;		f >> lab;
//		V_label.push_back(lab);
	}
}
