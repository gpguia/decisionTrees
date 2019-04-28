#ifndef ID3_HPP
#define ID3_HPP

#include "dtree.hpp"
#include <map>

#define MP make_pair

class ID3{
private:
	string searchSame(VDATA data, int id_col);
	string searchMostCommon(VDATA data, int id_col);
	int gain(VDATA data, int id_col);
	double entropy(vector <double> p);
public:	
	ID3();
	virtual ~ID3();	
	node* doID3(VDATA data, VDATA info, int id_col);
};

#endif