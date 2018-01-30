#include "Cache.h"
using namespace std;
#define test

//	insert data to set named voca	and		emotionbar;
Cache::Cache(const string &fname, bool T){
	char c;
	int lines=0;
	bool SizeFirstLine=true;
	fstream ftry(fname, ios::in);
	while((c=ftry.get()) != EOF){
		if(c == ','&&SizeFirstLine==true){
			Attrnum++;
		}else if(c == '\n'){
			lines++;
			SizeFirstLine = false;
		}
	}
	if (T) {
		Attrnum++;
	}
	printf("[Cache]/cache:num of attributes=%d\n", Attrnum);
	printf("[Cache]/cache:samplelines=%d\n", lines);
	
	fstream f(fname, ios::in);
	for(int l=0; l<lines; l++){
		vector<double> xv; 
		for(int i=0; i<Attrnum; i++){
			double xi;	f >> xi;
			//cout << setw(4) << xi;
			char c = ',';
			if(T == false)	f >> c;
			else
			{
				if (i == Attrnum - 1);
				else f >> c;
			}
			//cout << setw(4) << c;
			if(c != ','||c == '\n'){
				printf("[Cache]:You have changed the format of the file.\n");
				system("pause");
			}
			xv.push_back(xi);
		}

		int label;	
		if (T == false) f >> label;
//		cout << label << endl;
		
		Tuple tp;
		tp.attr = xv;
		if(T == false)		tp.label = label;
		cachebase.push_back(tp);
		labelbase.push_back(label);
	}
	printf("[Cache]:Information extracting done.\n");
}

int Cache::getsize(){
	return labelbase.size();
}

int Cache::getattrnum(){
	return Attrnum;
}






















