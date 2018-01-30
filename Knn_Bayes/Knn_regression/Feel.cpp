#include <bits/stdc++.h>
#include "Feel.h"
using namespace std;

vector<double> output;

void Feel::setfeel(vector<double> fb){
	feelbar = fb;
	anger = fb[0];
	disgust = fb[1];
	fear = fb[2];
	joy = fb[3];
	sad = fb[4];
	surprise = fb[5];
}

void Feel::visit_feelbar(){
	string sb[] = {"anger", "disgust", "fear", "joy", "sad", "surprise"};
	for(int i=0; i<feelbar.size(); i++){
		output.push_back(feelbar[i]);
//		cout << sb[i] << ':' << feelbar[i] << '\n';
	}
	
}
