#pragma once
#include <vector>
#include <string>
#include "..//SharedCode/AbstractFile.h"
#include "AbstractFileVisitor.h"
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
	vector<char> read();
	int getImageSize();
	void accept(AbstractFileVisitor* visitor) {
		if (visitor) {
			visitor->visit_ImageFile(this);
		}
	}
};


