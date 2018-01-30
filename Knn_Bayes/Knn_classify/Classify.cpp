#include <bits/stdc++.h>
#include "Tuple.h"
using namespace std;

struct Candylabel{
	Candylabel(double dst, string lb){
		distance = dst;
		label = lb;
	}
	double distance;
	string label;
};

bool labelCmp(const Candylabel &a, const Candylabel &b){
	return (a.distance < b.distance);
}

#define Most 
//	classify a new tuple to a label of tuplebase;
string classify(Tuple tp, int n)
{
//	check all tuples and get the list of labels;
	vector<Candylabel> labelbase;
	for(int i=0; i<Tuplebase.size(); i++){
		double crt_dst = tp.Distanceof(Tuplebase[i]);
		string crt_label = Tuplebase[i].label;
		Candylabel cl(crt_dst, crt_label);
		labelbase.push_back(cl);
	}
	sort(labelbase.begin(), labelbase.end(), labelCmp);

	#ifdef Most
	map<string, int> labelnum;
	int max_num = 0;
	string best_label;
	for(int i=0; i<n; i++){
		labelnum[labelbase[i].label] += 1;
		int cnt = labelnum[labelbase[i].label];
//		cout << labelbase[i].label << ':' << labelnum[labelbase[i].label] << endl;
		if(cnt >= max_num){
			max_num = cnt;
			best_label = labelbase[i].label;
		}
	}
//	cout << "label:" << best_label << endl;
	#endif
	#ifndef Most
//	find a key word;
	
//	calculating the posibilities;
	map<string, double> labelwgt;
	double sum_distance=0, sum_wgt=0;
	for(int i=0; i<n; i++)	sum_distance += labelbase[i].distance;
	for(int i=0; i<n; i++){
		labelwgt[labelbase[i].label] += abs(log( sum_distance/(labelbase[i].distance)) );
		sum_wgt += abs(log( sum_distance/(labelbase[i].distance)) );
	}
	
//	ready out all of the posibility;
	double max_posibility = 0;
	string best_label;
	for(map<string, double>::iterator it=labelwgt.begin(); it!=labelwgt.end(); it++){
		string crt_label = it->first;
		double crt_wgt = it->second;
//		cout << crt_label << ':' << crt_wgt/sum_wgt << endl;
		if(crt_wgt > max_posibility){
			max_posibility = crt_wgt;
			best_label = crt_label;
		}
	}
	#endif
	
	Forout_label.push_back(best_label);
//	system("pause");
	return best_label;
}

