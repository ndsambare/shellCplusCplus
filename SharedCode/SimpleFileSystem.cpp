// define methods of SimpleFileSystem class here
#include "AbstractFile.h"
#include "SimpleFileSystem.h"
#include "AbstractFileSystem.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <string>
#include <vector>
using namespace std; 


int SimpleFileSystem::closeFile(AbstractFile* pointerFile) {
;
	if (this->currFilesOpen.find(pointerFile) == currFilesOpen.end()) {
		return notOpen;
	}
	this->currFilesOpen.erase(pointerFile);
	return Succ;
}

int SimpleFileSystem::deleteFile(string nameOfFile) {
	if (this->fileInSystem.find(nameOfFile) == fileInSystem.end()) {
		return fileDoesNotExist;
	}

	if (currFilesOpen.find(this->fileInSystem[nameOfFile]) != currFilesOpen.end()) {
		return openIsFile;
	}
	auto erased = this->fileInSystem[nameOfFile];
	this->fileInSystem.erase(nameOfFile);
	delete erased;
	return Succ;
}

int SimpleFileSystem::createFile(string nameOfFile) {
	if (this->fileInSystem.find(nameOfFile) != fileInSystem.end()) {
		return fileExists;
	}
	int periodIndex = nameOfFile.find('.');
	string fileExtension = nameOfFile.substr((periodIndex + 1), nameOfFile.length());

	string img = "img";
	string txt = "txt";
	if (fileExtension.compare(img) == 0) {
		ImageFile* newFile = new ImageFile(nameOfFile);
		pair<string, AbstractFile*> enterFile;
		enterFile.first = nameOfFile;
		enterFile.second = newFile;
		fileInSystem.insert(enterFile);
		return Succ; 
	}
	if (fileExtension.compare(txt) == 0) {
		TextFile* newFile = new TextFile(nameOfFile);
		pair<string, AbstractFile*> enterFile;
		enterFile.first = nameOfFile;
		enterFile.second = newFile;
		fileInSystem.insert(enterFile);
		return Succ; 
	}
}





AbstractFile* SimpleFileSystem::openFile(string nameOfFile) {
	if (this->fileInSystem.find(nameOfFile) == fileInSystem.end() || (this->currFilesOpen.find(this->fileInSystem[nameOfFile]) != currFilesOpen.end())) {
		return nullptr;
	}

	currFilesOpen.insert(this->fileInSystem[nameOfFile]);
	return this->fileInSystem[nameOfFile];
}


int SimpleFileSystem::addFile(string nameOfFile, AbstractFile* pointerFile) {
	if (this->fileInSystem.find(nameOfFile) != fileInSystem.end()) {
		return fileExists;
	}
	if (pointerFile == nullptr) {
		return nullPointer; 
	}
	pair<string, AbstractFile*> enterFile;
	enterFile.first = nameOfFile;
	enterFile.second = pointerFile;
	fileInSystem.insert(enterFile);
	return Succ;
}

