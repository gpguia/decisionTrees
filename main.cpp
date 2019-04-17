#include <iostream>
#include "read.hpp"


using namespace std;

int main(int argc, char* argv[]){
	if(argc == 1){
		cout << "Please read the README file. \n";
		exit(1);
	}
	
	Read *r = new Read();
	r->readInput();
	
	return 0;	
}