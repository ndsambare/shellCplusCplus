// studio 18 - simple file factory definitions

#include "SimpleFileFactory.h"
#include "ImageFile.h"
#include "TextFile.h"


AbstractFile* SimpleFileFactory::createFile(string nameOfFile) {
	int periodIndex = nameOfFile.find('.');
	string fileExtension = nameOfFile.substr((periodIndex + 1), nameOfFile.length());
	string img = "img";
	string txt = "txt";
	if (fileExtension.compare(img) == 0) {
		ImageFile* newFile = new ImageFile(nameOfFile);
		pair<string, AbstractFile*> enterFile;
		enterFile.first = nameOfFile;
		enterFile.second = newFile;
		return newFile;
	}
	if (fileExtension.compare(txt) == 0) {
		TextFile* newFile = new TextFile(nameOfFile);
		pair<string, AbstractFile*> enterFile;
		enterFile.first = nameOfFile;
		enterFile.second = newFile;
		return newFile;
	}
	else {
		return nullptr;
	}
}