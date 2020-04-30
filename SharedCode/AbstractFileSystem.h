#pragma once
// declaration of the interface all file systems provide goes here
#include <vector>
#include <string>
#include "AbstractFile.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

class AbstractFileSystem {
public:
	virtual int addFile(string nameOfFile, AbstractFile* pointerFile) = 0;
	//virtual int createFile(string nameOfFile) = 0;
	virtual int deleteFile(string nameOfFile) = 0;
	virtual AbstractFile* openFile(string nameOfFile) = 0;
	virtual int closeFile(AbstractFile* pointerFile) = 0;
	virtual set<string> getFileNames() = 0;
};