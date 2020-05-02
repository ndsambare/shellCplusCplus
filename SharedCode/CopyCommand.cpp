#include "CopyCommand.h"
#include "MetadataDisplayVisitor.h"
#include "PasswordProxy.h"
#include <map>
#include <sstream>
#include <string>
#include <iostream>

CopyCommand::CopyCommand(AbstractFileSystem* afsInput) {
	this->afs = afsInput;
}

int CopyCommand::execute(string command) {
	istringstream iss(command);
	string fileName, newFile;
	iss >> fileName >> newFile;
	AbstractFile* file = afs->openFile(fileName);
	afs->closeFile(file);
	if (file == nullptr) {
		return fileDoesNotExist;
	}
	string copiedFileName = newFile + fileName.substr(fileName.find("."));
	//check if file exists
	AbstractFile* copiedFile = file->clone(copiedFileName);
	//PasswordProxy* passCopy = new PasswordProxy(copiedFileName,)
	return afs->addFile(copiedFileName, copiedFile);
}
void CopyCommand::displayInfo() {
	cout << "Enter data you would like to write to the file. Enter :wq to save and quit, enter :q to exit without saving." << endl;
}