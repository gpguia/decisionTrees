#include "id3.hpp"

ID3::ID3(){
	
}

ID3::~ID3(){
	
}

node* ID3::doID3(VDATA data, VDATA info, int id_col){
	node *r2 = (node*) new node;
	int best_col;
	string lbl,sub_vi;
	VDATA attrA;
	vector<string> nv,exVect;
	map <pair <string,string>, int> attrlab;
	map <string,int> lab;
	map <string, int> attr;
	map <pair <string,string>, int>::iterator it;
	map <string, int>::iterator it2;
	
		
	
}