#include"Comment.h"
#include<bits\stdc++.h>
#include<iostream>
#include"Compute.h"
using namespace std;

//vector<string> dictionary;
vector<string> keybase;
vector<unsigned int> keycnt;
unsigned int mstFreq = 0;

#define DVD
void static dvd() {
#ifdef DVD
	for (unsigned short i = 0; i < 20; i++) {
		printf("-");
	}cout << endl;
#endif // DVD
}

void static ToLowerString(string &str) {
	transform(str.begin(), str.end(), str.begin(), (int(*)(int))tolower);
}

static vector<string> beact;
bool static InitBeAct() {
	if (beact.size() == 0) {
		beact.push_back("am");
		beact.push_back("is");
		beact.push_back("are");
		beact.push_back("was");
		beact.push_back("were");
	}
	else {
		return true;
	}
	return true;
}

static vector<string> commas;
bool InitComma() {
	if (commas.size() == 0) {
		fstream fcomma("comma.txt", ios::in);
		char c;
		string cma;
		while ((c=fcomma.get()) != EOF){
			if (c == '/') {
				while ((c = fcomma.get() != '\n'));
				c = fcomma.get();
			}
			cma += c;
		}
		stringstream ss;
		ss.str("");
		ss.clear();
		ss.str(cma);
		while (!ss.fail()){
			string crts;
			ss >> crts;
			commas.push_back(crts);
		}
		return true;
	}
	else {
		return true;
	}
}
bool static isComma(const string &str) {
	if (str == "n't" || str == "isn't" || str == "'t") {
		return false;
	}
	bool iscomma = false;
	vector<string>::iterator it;
	it = find(commas.begin(), commas.end(), str.c_str());
	if (it != commas.end()) {
		iscomma = true;
	}
	else {
		for (unsigned short spin = 0; spin < str.size(); spin++) {
			char regc = str[spin];
			if (regc < -1 || regc > 255) {
				return true;
			}
			if(isalpha(regc)){}
			else{
				iscomma = true;
				break;
			}
		}
	}
	return iscomma;
}

bool static InsertUnique(vector<string> &vect, string word) {
	vector<string>::iterator it;
	it = find(vect.begin(), vect.end(), word);
	if (it != vect.end()) {
		return false;
	}
	else vect.push_back(word);
	return true;
}

Comment::Comment(){}
Comment::~Comment(){}
Comment::Comment(const string &commenttext, bool expandKeyBase) {
	stringstream ss;
	ss.str("");
	ss.clear();
	ss.str(commenttext);
	while (!ss.fail()) {
		string crts;
		ss >> crts;
		if (isComma(crts)) {}
		else {
			if (crts.size() >= 3)
				InsertUnique(comment, crts);
		}
	}
	deConstruct(expandKeyBase);
}

void Comment::showComment() {
	for (unsigned short cmpin = 0; cmpin < comment.size(); cmpin++) {
		cout << comment[cmpin] << ' ';
	}cout << endl;
}

bool Comment::isBeAct(const string &str) {
	InitBeAct();
	vector<string>::iterator it;
	it = find(beact.begin(), beact.end(), str);
	if (it == beact.end())	return false;
	else return true;
}

void Comment::deConstruct(bool expand) {
	bool love = false;
	for (unsigned short cpin = 0; cpin < comment.size(); cpin++) {
		//dictionary.push_back(comment[cpin]);
		if (!expand && !love) {
			if (comment[cpin] == "love" || comment[cpin] == "loves") {
				love = true;
			}
		}

		if (isBeAct(comment[cpin]) && expand) {
			if ((cpin + 1) < comment.size()) {
				cpin++;
				if (comment[cpin].size() >= 3 && expand) {
					//Keep a sequence of key words and a sequence of its count;
					string crts = comment[cpin];
					if (keybase.empty()) {
						keybase.push_back(crts);
						keycnt.push_back(1);
					}else{
						bool exist = false;
						for (unsigned int kpin = 0; kpin < keybase.size()&&!keybase.empty(); kpin++) {
							if (keybase[kpin] == crts) {
								exist = true;
								keycnt[kpin]++;
								if(crts != "not"&&crts != "good"
									&&crts != "nice"&&crts != "great")
									mstFreq = max(mstFreq, keycnt[kpin]);
							}
						}
						if (!exist) {
							keybase.push_back(crts);
							keycnt.push_back(1);
						}
					}
				}
				//unsigned short stt = 0;
				//if (cpin > 2)	stt = cpin - 2;
				comment.erase(comment.begin(), comment.begin() + cpin);
			}
		}
	}
	if (love && !expand) {
		comment.push_back("good");
		comment.push_back("great");
		comment.push_back("nice");
		comment.push_back("super");
		comment.push_back("amazing");
		comment.push_back("friendly");
		comment.push_back("pleasantly");
		comment.push_back("perfect");
		comment.push_back("excited");
		comment.push_back("amazing");
		comment.push_back("surprised");
		comment.push_back("cool");
		comment.push_back("well");
		comment.push_back("sweet");
		comment.push_back("best");
		comment.push_back("excellent");
	}
}

unsigned int Comment::getCommentSize() {
	return comment.size();
}

vector<string> Comment::getCommmentWord() {
	return comment;
}


// Implement of Serial Comment, dealing with one user's comment;
// maybe consists several sentences;

SerialComment::SerialComment(){}
SerialComment::~SerialComment(){}

SerialComment::SerialComment(const string &message, const bool &expandKeyBase){
	stringstream ss;
	ss.str("");
	ss.clear();
	ss.str(message);
	
	bool isLevel = true;
	string linebuffer;
	while (!ss.fail()) {
		string crts;
		ss >> crts;
		if (isLevel) {
			isLevel = false;
			level = crts;
		}
		else {
			if (crts == "<sssss>") {
				Comment tmp(linebuffer, expandKeyBase);
				if (tmp.getCommentSize() > 0)	usermsg.push_back(tmp);
				linebuffer.clear();
			}
			else {
				if (crts == "n't" || crts == "isn't" || crts == "'t")
					crts = "not";
				linebuffer += crts;
				linebuffer += " ";
			}
		}
	}
	Comment tmp(linebuffer, expandKeyBase);
	if(tmp.getCommentSize() > 0)	usermsg.push_back(tmp);
}

void SerialComment::showMsg() {
	printf("[SerialComment]showMsg: Showing user msg:\n");
	dvd();
	for (unsigned int l = 0; l < usermsg.size(); l++) {
		usermsg[l].showComment();
	}
	dvd();
	printf("[SerialComment]showMsg: done.\n");
}

// collect all words in the user's comment to analyze
vector<double> SerialComment::getDigits() {
	vector<string> keyword;
	vector<double> wordfreq;
	for (unsigned int mpin = 0; mpin < usermsg.size(); mpin++) {
		Comment crtcmt = usermsg[mpin];
		vector<string> crtv = crtcmt.getCommmentWord();
		for (unsigned int vpin = 0; vpin < crtv.size(); vpin++) {
			string crts = crtv[vpin];
			keyword.push_back(crts);
		}
	}
	wordfreq = wordFreq(keybase, keyword);
	return wordfreq;
}

double SerialComment::getLevel() {
	if (level == "LOW"||level == "low") {
		return 0.0;
	}
	else if (level == "MID"||level == "mid") {
		return 0.6;
	}
	else {
		return 1.2;
	}
}