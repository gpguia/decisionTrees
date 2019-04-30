#ifndef DTREE_HPP
#define DTREE_HPP

#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <fstream>
#include <iomanip>

using namespace std;

#define VDATA vector< vector<string> >

typedef struct _node{
	bool leaf;
	string lbl;
	int count;
	vector<pair<string, _node*> > child;
}node;

VDATA readInput(string path);
void print(VDATA p);
vector<string> split(string s);
void printData(VDATA data);
void checkNumCols(VDATA *data);
bool isNum(const string s);
void qsort(VDATA *data, int low, int high, int col);
void sswap(VDATA *data, int begin, int end, string s, int col);
void printTree(node *r, int num);

#endif