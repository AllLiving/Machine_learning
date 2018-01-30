#ifndef DECISION_TREE_ANS_STREAM
#define DECISION_TREE_ANS_STREAM

class AnsStream {
public:
	AnsStream(const vector<int>&);
	void writeFile(const char*);
	void test(const vector<int>&, bool = 1);//bool为输出开关，默认为开(true)
	double Point();
	double Accuray();
	double Precision();
	double F1();
private:
	int* data;
	int length;
	double accuray, recall, precision, f1;
};

#endif