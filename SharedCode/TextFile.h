#pragma once
// TextFile declaration goes here

#include <vector>
#include <string>
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
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
	vector<char> read();
	string getName();
	void accept(AbstractFileVisitor* visitor) {
		if (visitor) {
			visitor->visit_TextFile(this);
		}
	}



};