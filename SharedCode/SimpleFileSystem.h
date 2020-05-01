#pragma once
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

// declaration of SimpleFileSystem class goes here
class SimpleFileSystem : public AbstractFileSystem {
public:
	virtual int addFile(string nameOfFile, AbstractFile* pointerFile);
	//virtual int createFile(string nameOfFile);
	virtual int deleteFile(string nameOfFile);
	virtual AbstractFile* openFile(string nameOfFile);
	virtual int closeFile(AbstractFile* pointerFile);
	virtual set<string> getFileNames();

private:
	map<string, AbstractFile*> fileInSystem;
	set<AbstractFile*> currFilesOpen;

};