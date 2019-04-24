#ifndef ID3_HPP
#define ID3_HPP

#include "dtree.hpp"
#include <map>


class ID3{
private:
public:	
	ID3();
	virtual ~ID3();	
	node* doID3(VDATA data, VDATA info, int id_col);
};

#endif