#pragma once
// declare AbstractFile here. As all methods are virtual and will not be defined, no .cpp file is necessary
#include <string>
#include <vector>

class AbstractFileVisitor;
using namespace std; 

enum failsOrSuccess {
	Success = 0, IncorrectChar = 1, sizeMisMatch = 2, appendNotSupported = 3, wrongPass = 4,
};

class AbstractFile {
public:
	virtual vector<char> read() = 0;
	virtual int write(vector<char> c) = 0;
	virtual string getName() = 0;
	virtual int append(vector<char> c) = 0;
	virtual unsigned int getSize() = 0;
	virtual ~AbstractFile() = default;
	virtual void accept(AbstractFileVisitor* visitor) = 0;
};