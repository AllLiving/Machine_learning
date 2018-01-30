#include <bits/stdc++.h>
using namespace std;

void split(string fname){
	char c;
	
	int attrnum=0;
	int lines=0;
	bool nowweatthefirstline=true;
	fstream ftry(fname, ios::in);
	printf("Be going to read...\n");
	while((c=ftry.get()) != EOF){
		if(c == ','&&nowweatthefirstline==true){
			attrnum++;
		}else if(c == '\n'){
			lines++;
			nowweatthefirstline = false;
		}
	}
	lines++;
	
	printf("num of attributes=%d\n", attrnum);
	printf("samplelines=%d\n", lines);
	
	fstream f(fname, ios::in);
	fstream ft("TT.csv", ios::out);
	fstream fv("Valid.csv", ios::out);
	for(int l=0; l<lines; l++){
		vector<double> xv; 
		if(((l+1)%3) == 0){
			for(int i=0; i<attrnum; i++){
				double xi;	f >> xi;
				fv << xi << ',';
				char c;		f >> c;
				if(c != ','||c == '\n'){ 
					printf("the char=");
					cout << c << endl;
					printf("[train]:You have changed the format of the file.\n");
					system("pause");
				}
				xv.push_back(xi);
			}
			short label;	f >> label;
			fv << label << endl;
		}else{
			for(int i=0; i<attrnum; i++){
				double xi;	f >> xi;
				ft << xi << ',';
				char c;		f >> c;
				if(c != ','||c == '\n'){ 
					printf("the char=");
					cout << c << endl;
					printf("[train]:You have changed the format of the file.\n");
					system("pause");
				}
				xv.push_back(xi);
			}
			short label;	f >> label;
			ft << label << endl;
		}
	}
	printf("[Split]:Information extracting done.\n");
}

int main(){
	string fname = "train.csv";
	
	train(fname);
	return 0;
}
