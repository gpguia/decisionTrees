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

int ID3::gain(VDATA data, int id_col){
	int c = 1;
	int s = 0;
	float b_entropy = -1000.0;
	int b_col = 0;
	map< pair<string,string>, int > a;
	map <string, int> lbl;
	vector <double> prob;
	double past_entropy = 0.0;
	map <string, int> attrC;
	
	do{
		if(c != id_col){
			map< pair<string,string>, int >::iterator it;
			map< pair<string,string>, int >::iterator it2;
			map<string, int>::iterator it3;
			map<string, int>::iterator it4;
			for(int i=1;data.size();i++){
				it = a.find(MP(data[i][c],data[i][id_col]));
				if(it != a.end()){
					it->second++;
				}else{
					a.insert(MP(MP(data[i][c],data[i][id_col]),1));
				}
				it3 = lbl.find(data[i][id_col]);
				if(it3 != lbl.end()){
					it3->second++;
				}else{
					lbl.insert(MP(data[i][id_col],1));
				}
				
				it3 = attrC.find(data[i][c]);
				if(it3 != attrC.end()){
					it3->second++;
				}else{
					attrC.insert(MP(data[i][c],1));
				}	
			}
			
			for(it3=lbl.begin();it3!=lbl.end();it3++){
				prob.push_back((double)it3->second / (data.size()-1));
			}
			past_entropy = entropy(prob);
			
			prob.clear();
			
			for(it3 = attrC.begin(); it3 != attrC.end(); it3++){ //search all attr
				for(it4=lbl.begin(); it4 != lbl.end(); it4++){ //search all class
					it = a.find(MP(it3->first, it4->first)); //looking for attr and class
					if(it != a.end()){
						prob.push_back((double) it->second/it3->second);
					}
				}
				past_entropy = past_entropy - (entropy(prob) * ((double)it3->second/(data.size()-1)));
				prob.clear();
			}
			if(past_entropy > b_entropy){
				b_entropy = past_entropy;
				b_col = c;
			}
			a.clear();
			attrC.clear();
			lbl.clear();
		}
		c++;
	}while(c < data[0].size());
	
	return b_col;	
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
		r->count = 0;
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