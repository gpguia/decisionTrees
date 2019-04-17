#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <string>

class Table{
private:
public:
	Table();
	virtual ~Table();
	
	vector<string> attr; //attr, first line of csv.
	vector<vector<string>> table; //table, all the values in csv.
	
	int target; //taget column
	int id_col; //id column
	int size; //how many examples
	
	bool gain; //if true is using gain, if false is using entropy
	
	
};

#endif