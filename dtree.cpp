#include "dtree.hpp"
#include "id3.hpp"

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "Please read the README file. \n";
		exit(1);
	}
	
	VDATA data; //table, all data from input
	data = readInput(argv[1]);
	int id_col; //target column
	cout << "Target column: ";
	cin >> id_col;
	
	node* r; //root
	
	checkNumCols(&data);
	
	ID3 *id3 = new ID3();
	r = id3->doID3(data,data,id_col);
	printTree(r,0);
	
	//falta classificar
	
	return 0;	
}

//Split comma
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

//get intput, you can eather use ./dtree OPTION < inputfile or use make for it
VDATA readInput(string path){
	vector <vector<string> > in;
	string l;
	
	ifstream f (path.c_str());
	
	if(f.is_open()){
		while(getline(f, l)){
			in.push_back(split(l));
		}
		f.close();
	}else{
		cout << "File not found or error while openning. \n";
		exit(1);	
	}	
	return in;
}

//Print data vector
void printData(VDATA data){
	unsigned int i,j;
	
	for(i=0;i<data.size();i++){
		for(j=0;j< data[i].size() ; j++){
			cout << data[i][j].c_str() << "\t";
		}
		cout << endl;
	}
}


//got it from: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
//just to check if a string is a number or not, only work for positive numbers.
bool isNum(const string s){ 
	string::const_iterator it = s.begin();
  while (it != s.end() && isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

//quicksort by column
void qsort(VDATA *data, int low, int high, int col){
	float pivot = stod((*data)[(low+high)/2][col]);
	vector<string> aux;
	int i = low;
	int j = high;
	
	while(i<=j){
		while(stod((*data)[i][col])<pivot)
			i++;
			
		while(stod((*data)[j][col])>pivot)
			j--;
			
		if(i<=j){
			aux = (*data)[i];
			(*data)[i] = (*data)[j];
			(*data)[j] = aux;
			i++;
			j--;
		}	
	}	
	
	if(low < j)
		qsort(data,low,j,col);
	if(high > i)
		qsort(data,i,high,col);
	
}

//swap strings in data
void sswap(VDATA *data, int begin, int end, string s, int col){
	for(int i=begin;i<=end;i++){
		(*data)[i][col] = s;
	}	
}

//check columns that are number
void checkNumCols(VDATA *data){
	
	int begin, end,count;
	string lim1,lim2,cur,v;
	stringstream ss;
	
	for(int col; col < (*data)[1].size();col++){
		if(isNum((*data)[1][col])){
			qsort(data,1,data->size()-1,col);
			lim1 = (*data)[1][col];
			begin = 1;
			count=1;
			cur = (*data)[1][(*data)[1].size()-1];
			
			for(int i=2;i<data->size();i++){
				if((*data)[i][(*data)[i].size()-1] == cur && i != data->size()-1){
					lim2=(*data)[i][col];
					count++;
					end=i;
				}else if(count<2 && i != data->size()-1){
					lim2 = (*data)[i][col];
					count++;
					end=i;
					cur=(*data)[i][(*data)[i].size()-1];
				}else if(i == data->size()-1){
					end = i;
					v = (*data)[i][col];
					sswap(data,begin,end,">" + v, col);
				}else{
					ss << fixed << setprecision(2) << (stof(lim2) + stof((*data)[i][col]))/2;
					v = ss.str();
					ss.str("");
					if(begin == 1)
						sswap(data,begin,end,"<" + v, col);
					else
						sswap(data,begin,end,lim1 + "-" + v, col);
						
					lim1 = v;
					count = 1;
					begin = i;
					cur = (*data)[i][(*data)[1].size()-1];
				}
			}
			
		}	
	}
}

void printTree(node *r, int num){
	if(r == NULL){
		printf("Node is null");
		exit(1);
	}
	if(r->leaf){
		cout << " " << r->lbl << " (" <<	 r->count <<")" << endl;
	}else{
		if(num != 0)
			cout << endl;	
		
		for(int i=0;i<num;i++)
			cout << "\t";	
		if(num != 0){
			cout << "\t";
			num++;
		}
		cout << "<" << r->lbl << ">\n";
		for(int i=0;i<(r->child).size();i++){
			for(int j=0;j<=num;j++){
				cout << "\t";
			}
			cout << (r->child)[i].first << ":";
			printTree((r->child)[i].second,num+1);
		}
	}
}