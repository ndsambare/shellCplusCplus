#pragma once
#include <vector>
#include <string>
#include "..//SharedCode/AbstractFile.h"
// Image file class declaration here

class ImageFile : public AbstractFile {
private: 
	string fileName; 
	vector<char> fileContent; 
	char imageSize;
	int coordinateToIndex(unsigned int x, unsigned int y);

public: 
	ImageFile(string name);
	unsigned int getSize();
	string getName();
	int write(vector<char> c);
	int append(vector<char> a);
	void read();
};


enum failsOrSuccess {
	Success = 0, IncorrectChar = 1, sizeMisMatch = 2, appendNotSupported = 3,
};