#include "TouchCommand.h"
#include "SimpleFileSystem.h"
#include "PasswordProxy.h"
#include <sstream>

TouchCommand::TouchCommand(AbstractFileSystem* afsInput, AbstractFileFactory* affInput) {
	this->afs = afsInput;
	this->aff = affInput;
}

int TouchCommand::execute(string command) {
	istringstream iss(command);
	string fileName, passCheck;
	iss >> fileName >> passCheck;
	AbstractFile* file = aff->createFile(fileName);
	if (file == nullptr) {
		return nullPointer;
	}
	int result;
	//password
	if (passCheck == "-p") {
		cout << "What is the password?" << endl;
		string pass;
		cin >> pass;
		PasswordProxy* pp = new PasswordProxy(file, pass);
		result = afs->addFile(fileName, pp);
	}
	else {
		result = afs->addFile(fileName, file);
	}
	if (result == fileExists) {
		return fileExists;
	}
	else if (result != Succ) {
		afs->deleteFile(fileName);
	}
	return result;
}
void TouchCommand::displayInfo() {
	cout << "Touch creates a file, touch can be invoked ith the command : touch <filename>" << endl;
}