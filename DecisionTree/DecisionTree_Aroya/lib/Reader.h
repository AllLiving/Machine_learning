#ifndef AROYA_READER
#define AROYA_READER

class Reader {//之前Lab文件读取对象
public:
	Reader(const char*);
	//~Reader();
	vector<vector<int>>data;
	vector<int>flag;
	int columns, rows;
};

#endif