#include "id3.hpp"

ID3::ID3(){
	
}

ID3::~ID3(){
	
}

string ID3::searchSame(VDATA data, int id_col){
	string rlbl;
	if(data.size() > 1)
		rlbl = data[1][id_col];
	
	for(int i = 1; i < data.size(); i++){
		if(data[i][id_col].compare(rlbl)){
			return "";
		}
	}
	return rlbl;
}

string ID3::searchMostCommon(VDATA data, int id_col){
	string lbl;
	
	int max = 0;
	map<string, int> c;
	map<string, int>::iterator it;
	
	for(int i=1; i<data.size(); i++){
		it = c.find(data[i][id_col]);
		if(it != c.end()){ //found 
			it->second++;	
		}else{
			c.insert(MP(data[i][id_col],1));	
		}
	}	
	
	for(it = c.begin(); it != c.end(); it++){ //get the most common 
		if(it->second > 0){
			max = it->second;
			lbl = it->first;
		}
	}
	
	return lbl;
}
	
node* ID3::doID3(VDATA data, VDATA info, int id_col){
	node *r = (node*) new node;
	int best_col;
	string lbl,sub_vi;
	VDATA attrA;
	vector<string> nv,exVect;
	map <pair <string,string>, int> attrlab;
	map <string,int> lab;
	map <string, int> attr;
	map <pair <string,string>, int>::iterator it;
	map <string, int>::iterator it2;
	
	lbl = searchSame(data, id_col);
	 
	if(lbl != ""){
		r->leaf = true;
		r->count = data.size()-1;
		r->lbl = lbl;
		return r;
	}
	
	if(info[0].size() == 2){ //there is no more attr
		lbl = searchMostCommon(data, id_col);
		root->count = 0;
		for(int i = 0; i< data.size(); i++){
			if(data[i][id_col] == lbl){
				r->count++;
			}
		}
		r->leaf = true;
		r->lbl = lbl;
		return r;
	}else{
		r->leaf = false;
		best_col = gain(data, id_col);
		
	}
	
}