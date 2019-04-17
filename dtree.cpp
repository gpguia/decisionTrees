#include "dtree.hpp"


using namespace std;

int main(int argc, char* argv[]){
	if(argc == 1){
		cout << "Please read the README file. \n";
		exit(1);
	}
	
	vector < vector<string> > data; //table, all data from input
	data = readInput();
	int id_col; //target column
	cout << "Target column: ";
	cin >> id_col;
	
	
	
	
	return 0;	
}

vector<string> split(string s){
	vector <string> w;
	size_t i = 0;
	string tok;
	while((i = s.find(",")) != string::npos){
		tok = s.substr(0,i);
		w.push_back(tok);
		s.erase(0,i + 1);
	}
	w.push_back(s);
	return w;
}

vector < vector <string> > readInput(){
	vector <vector<string> > in;
	string l;
	
  cin >> l; //read first line
	
	while(l.front() != '\0'){
		in.push_back(split(l));
		l.erase(); //to be able to stop reading input
		cin >> l;
	}
	
	return in;
}

void printData(vector < vector<string> > data){
	unsigned int i,j;
	
	for(i=0 ; i < data.size() ; i++)
	{
		for(j=0 ; j < data[i].size() ; j++){
			printf("%-8s ", data[i][j].c_str());
		}
		cout << endl;
	}
}