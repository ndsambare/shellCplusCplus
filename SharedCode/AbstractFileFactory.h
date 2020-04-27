#pragma once
// studio 18 - file factory interface declared here

#include <string>
#include <vector>

class AbstractFile;

using namespace std;

class AbstractFileFactory {
public:
	virtual AbstractFile* createFile(string fileName) = 0;
};