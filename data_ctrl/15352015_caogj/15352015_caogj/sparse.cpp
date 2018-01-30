#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include <mutex> 
#include <thread>
using namespace std;

mutex mtx;
int line = 0, row = 0, rowmax = 0, datacnt = 0;

ofstream fout("smatrix.txt");
void print(int line, int row){
	mtx.lock(); 
	fout << line << ' ';
	fout << row << ' ';
	fout << 1 << endl;
	mtx.unlock();
} 

int main(){

	fstream f("onehot.txt", ios::in);
	char c;
	vector<thread> v;
	mtx.lock();
	while((c = f.get()) != EOF){
		if(c == '1'){
			datacnt++;
			int l = line;
			int r = row;
//			subthreads for printing sparse; 
			v.push_back(thread(print, l, r));
		}
		row++;
		if(c == '\n'){
			rowmax = row-1;
			row = 0;
			line++;
		}
	}
	
	fout << line << endl;
	fout << rowmax << endl;
	fout << datacnt << endl;
	mtx.unlock();
//	release the subthreads;
	for(auto& subthread : v){
		subthread.join();
	}
	
	printf("The matrix has been created done.\n");
	
	return 0;
}

