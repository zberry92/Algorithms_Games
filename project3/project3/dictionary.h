#ifndef DICTIONARY_CLASS
#define DICTIONARY_CLASS

#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

class dictionary{
public:
	void importWords();

private:
	vector<string> words;
};

void dictionary::importWords()
{
ifstream inFile;
string s;
int length =0;
inFile.open("dictionary");

if (!inFile) {
cout << "Unable to open file";
}

while(inFile >> s)
{
	words.push_back(s);
	length++;
	if(length%5000 == 0)
		cout<<length<< " words loaded"<<endl;
}

cout<<"Complete: " <<length<< " words loaded"<<endl;
	
}

#endif // DICTIONARY_CLASS