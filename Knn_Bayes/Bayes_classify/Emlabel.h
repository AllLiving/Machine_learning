#include <bits/stdc++.h>
using namespace std;

//extern vector<string> joylabel;
//extern vector<string> sadlabel;
//extern vector<string> disgustlabel;
//extern vector<string> surplabel;
//extern vector<string> angerlabel;
//extern vector<string> fearlabel;
extern int joyvocnt;
extern int sadvocnt;
extern int disgustvocnt;
extern int surprisevocnt;
extern int angervocnt;
extern int fearvocnt;

extern int get_size(string emotion, bool repeat);
extern int count_words(string emotion, string word);
extern void fillemlabel(string emotion, vector<string> LinkEmotionVocabularyBase);

extern vector<string> Read_label(string fname);
extern double Ratio(vector<string> va, vector<string> vb);
