#pragma once
// declare AbstractFile here. As all methods are virtual and will not be defined, no .cpp file is necessary
#include <string>
#include <vector>
using namespace std; 

class AbstractFile {
public:
	virtual void read() = 0;
	virtual int write(vector<char> c) = 0;
	virtual string getName() = 0;
	virtual int append(vector<char> c) = 0;
	virtual unsigned int getSize() = 0;
	
};