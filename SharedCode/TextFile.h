#pragma once
// TextFile declaration goes here

#include <vector>
#include <string>
#include "AbstractFile.h"
using namespace std;

class TextFile : public AbstractFile {

private:
	vector<char> fileContent;
	string fileName;

public:
	TextFile(string name);
	unsigned int getSize();
	int write(vector<char> c);
	int append(vector<char> c);
	void read();
	string getName();



};