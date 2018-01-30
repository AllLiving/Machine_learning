#include <bits/stdc++.h>
//#include <map>
using namespace std;

struct pos {
	pos() {	x = y = 0;	}
	pos(int x_, int y_){
		x = x_;
		y = y_;
	}
	bool operator == (const pos &a)const{
		return ((a.x == x) && (a.y == y));
	}
	int x, y;
};
struct comp{
	bool operator () (const pos &a, const pos &b)const
	{
		if(a.x != b.x){
			return (a.x < b.x);
		}else{
			return (a.y < b.y);
		}
	}
}; 

//比较困难的是数据结构的选择和处理，而非算法； 
map<pos, int, comp> AplusB(map<pos, int, comp> a, map<pos, int, comp> b){
//	遍历b，对各个元素逐一检查修整； 
	for(map<pos, int, comp>::iterator it=b.begin(); it!=b.end(); it++){
		pos pb = it->first;
		int value = it->second;
//		若a中出现了该位置坐标，数值叠加； 
		if(a[pb]){
			a[pb] += it->second;
		}else{
			a.insert(pair<pos, int>(pb, 0));//注意我插了个0； 
			a[pb] += value; 
		}
	}
	return a;
}

void print(map<pos, int, comp> c, ofstream fout){
	for(map<pos, int, comp>::iterator it=c.begin(); it != c.end(); it++){
		fout << it->first.x << ' ' << it->first.y << ' ' << (int)(it->second) << endl;
	}
}

int main() {
	fstream fus("A.txt", ios::in);
	fstream fme("B.txt", ios::in);
	
	map<pos, int, comp> a, b;

	int InputTimes = 2;
	while (InputTimes--) {
		printf("\nInputTimes=%d\n", InputTimes);

		int line, tmp;
		if(InputTimes)	fme >> tmp >> tmp >> line;
		else fus >> tmp >> tmp >> line;
		map<pos, int, comp> c;
		for (int i = 0; i < line; i++) {
			pos pn;
			int v;
			if(InputTimes)	fme >> pn.x >> pn.y >> v;
			else fus >> pn.x >> pn.y >> v;
			c.insert(pair<pos, int>(pn, v));
		}
		
//		print(c);
		
//		system("pause");

		if(InputTimes){
			a = c;
		}else{
			b = c;
		}
	}

	printf("\nChecking the output.\n");
	map<pos, int, comp> reslt;
	reslt = AplusB(a, b);
	ofstream fout("MatrixAddtion.txt");
	for(map<pos, int, comp>::iterator it=reslt.begin(); it != reslt.end(); it++){
		fout << it->first.x << ' ' << it->first.y << ' ' << (int)(it->second) << endl;
	}
//	print(reslt, fout);

	return 0;
}
