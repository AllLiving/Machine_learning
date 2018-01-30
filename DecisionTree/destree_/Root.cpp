#include <bits/stdc++.h>
#include "Root.h"
using namespace std;
#define INFOGAIN
//#define INFORATIO
//#define GINI

static void dvd(){
	for(int i=0; i<20; i++)
		printf("-");
	printf("\n");
}

Root::Root(){
	leafans = false;
}

//#define build_debug
bool Root::build(vector<vector<int>> Attr_set, vector<int> label){
	
	#ifdef build_debug
	printf("\n\n\nbegin building...\n");
	forset(Attr_set);
	for(int lbpin=0; lbpin<label.size(); lbpin++){
		cout << label[lbpin] << ' ';
	}cout << endl;
	#endif
	
	bool cls = true;
	for(int labelpin=0; labelpin<label.size(); labelpin++){
		if(label[labelpin] != label[0])
			cls = false;
	}
	
	#ifdef build_debug
	if(cls == true){
		printf("Finish classify.\n");
		dvd();
	}else if(Attr_set.size() == 1){
		printf("Only one Attribute to use.\n");
	}else if(Attr_set[0].size() == 1){
		printf("attribute clause.\n");
	}
	#endif
	
	if(cls == true ||
		Attr_set.size() == 1||
		Attr_set[0].size() == 1){
		leafans = true;
		ans = forans(label);
		return true;
	}
	
	double entropy = 0;
	int NOAttr=0;
	this->attr_set = Attr_set[0];
	this->label = label;
	
	if(Attr_set.size()>3)
		printf("\n\n\n[Root]/build:Selecting a root node...\n");
		
		
	for(int atpin=0; atpin<Attr_set.size(); atpin++){
		vector<int> attrset = Attr_set[atpin];
		
		#ifdef INFOGAIN
		double crt_epy = infogain(attrset, label);
		#endif
		
		#ifdef INFORATIO
		double crt_epy = inforatio(attrset, label);
		#endif
		
		#ifdef GINI
		double crt_epy = syn_gini(attrset, label);
		#endif
		
		if(Attr_set.size() > 3){
			printf("[Root]/build:attribute set:");
			for(int i=0; i<attrset.size(); i++){
				cout << attrset[i] << ' ';
			}cout << endl;
			printf("[Root]/build:current entropy=%lf\n", crt_epy);
		}
		if(crt_epy > entropy){
			entropy = crt_epy;
			this->attr_set = attrset;
			NOAttr = atpin;
		}
	}
	attr_index = NOAttr;
	
	#ifdef build_debug
	printf("We have decide to use %dth attribute.\n", attr_index);
	#endif
	
/*  
 *	split attr_set into several attr_set,
 *	as well as label
 *	sample diff crt_attr
 */
	vector<int> node_attr = this->attr_set;
	vector<int> attr_sample;
	int attr_kind = 0; 
	for(int i=0; i<node_attr.size(); i++){
		int crt_attr = node_attr[i];
		vector<int>::iterator it
			= find(attr_sample.begin(), attr_sample.end(), crt_attr);

		if(it == attr_sample.end()){
			attr_kind++;
			attr_sample.push_back(crt_attr);
		}
	}
	branch_option = attr_sample;
	
	#ifdef build_debug
	printf("%d branches is ready to build...\n", attr_kind);
	for(int smpin=0; smpin<branch_option.size(); smpin++){
		cout << attr_sample[smpin] << ' ';
	}cout << endl;
	#endif
	
/*
 *	KNOWN:
 *	attr_kind/ attr_sample
 *	from this breach attribute_set;
 *	branch grow, split attr_set and label;
 */
	for(int k=0; k<attr_kind; k++){
		int branch_attr = attr_sample[k];
		
		#ifdef build_debug
		printf("Constructing %dth branch: attr=%d\n", k, branch_attr);
		dvd();
		#endif

		vector<int> branch_label;
		vector<int> brchattr_log;
		for(int apin=0; apin<node_attr.size(); apin++){
			if(node_attr[apin] == branch_attr){
				brchattr_log.push_back(apin);
				branch_label.push_back(label[apin]);
				
				#ifdef build_debug
				printf("Now branch label sequence:\n");
				for(int bpin=0; bpin<branch_label.size(); bpin++){
					cout << branch_label[bpin] << ' ';
				}cout << endl;
				#endif
			}
		}
	
		vector<vector<int>> Attr;
/*	from Attr_set to Attr;  */
		for(int A=0; A<Attr_set.size(); A++){
			if(A == NOAttr)	continue;
			vector<int> cmpnt_Attr;
			for(int logpin=0; logpin<brchattr_log.size(); logpin++){
				int attr_log = brchattr_log[logpin];
				cmpnt_Attr.push_back(Attr_set[A][attr_log]);
			}
			Attr.push_back(cmpnt_Attr);
		}
		
		#ifdef build_debug
		printf("While the Attr become:\n");
		for(int i=0; i<Attr.size(); i++){
			vector<int> tmp_atr = Attr[i];
			for(int j=0; j<tmp_atr.size(); j++){
				cout << tmp_atr[j] << ' ';
			}cout << endl;
		}dvd();	
		#endif

/*  sent data into build function of Root**children   */
		Root *child = new Root();
		this->kidergarden.push_back(child);
		child->build(Attr, branch_label);
	}
	return true;
}

void Root::climb(string path){
	dvd();
	printf("Is a leaf node:");	cout << setw(5) << leafans << endl;
	printf("Attr index:");		cout << attr_index << endl;
	printf("Attribute set:\n");
	for(int aspin=0; aspin<attr_set.size(); aspin++){
		cout << attr_set[aspin] << ' ';
	}cout << endl;
	printf("Branch option size:");	cout << setw(5)  << branch_option.size() << endl;
	printf("Branch options:");
	for(int b=0; b<branch_option.size(); b++){
		cout << branch_option[b] << ' ';
	}cout << endl;
	printf("Attr index:");		cout << setw(5)  << attr_index << endl;
	printf("Label's size:");	cout << setw(5)  << label.size() << endl;
	for(int k=0; k<kidergarden.size(); k++){
		string branch_v = tostring(branch_option[k]);
		cout << "[Root] "<< path+branch_v<< ':';
		cout << endl;
	}
	dvd();
}

//#define debug
int new_cnt = 0;
int Root::getans(vector<int> attribute){
	
	if(leafans == true){
		return ans;
	}
	
	#ifdef debug 
	printf("\n[Root]/getans:Dealing attribute set:");
	for(int i=0; i<attribute.size(); i++){
		cout << attribute[i] << ' ';
	}
	printf("\n[Root]/getans:We will choose %dth attr:", attr_index);
	if(attr_index > attribute.size()){
		printf("attr_index wrong.\n");
	}else{
		cout << attribute[attr_index] << endl;
	}
	printf("[Root]/getans:We now have branches:");
	if(branch_option.size() == 0){
		printf("leaf node already.\n");
	}else{
		for(int i=0; i<branch_option.size(); i++){
			cout << branch_option[i] << ' ';
		}cout << endl;
	}
	#endif
	
	vector<int> atr = attribute;
	int crt_attr = atr[attr_index];
	
	bool recur = false;
	crt_attr = near_branch(crt_attr, branch_option);
	for(int brpin=0; brpin<branch_option.size(); brpin++){
		if(crt_attr == branch_option[brpin]){
			recur = true;
			atr.erase(atr.begin() + attr_index);
			return kidergarden[brpin]->getans(atr);
		}
	}
	if(recur == false){
//		brcs is short for branches;
		dvd();
		new_cnt++;
		cout << new_cnt;
		printf("Sorry, we cannot find your attribute in our branches.\n");
		printf("[Root]/getans/logs:We are checking the attributes:");
		for(int i=0; i<attribute.size(); i++){
			cout << attribute[i] << ' ';
		}
		printf("\n[Root]/getans/logs:While the branch options:");
		for(int i=0; i<branch_option.size(); i++){
			cout << branch_option[i] << ' ';
		}
		printf("\nNo exist data[%d] in %dth attr\n--Exit quit.\n", crt_attr, attr_index);	
		dvd();
	} 
}
