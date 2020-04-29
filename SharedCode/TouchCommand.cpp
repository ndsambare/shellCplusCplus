#include "TouchCommand.h"
#include "SimpleFileSystem.h"

TouchCommand::TouchCommand(AbstractFileSystem* afsInput, AbstractFileFactory* affInput) {
	this->afs = afsInput;
	this->aff = affInput;
}

int TouchCommand::execute(string command) {
	AbstractFile* file = aff->createFile(command);
	if (file == nullptr) {
		return nullPointer;
	}
	int result = afs->addFile(command, file);
	if (result == fileExists) {
		return fileExists;
	}
	else if (result != Succ) {
		afs->deleteFile(command);
	}
	return result;
}
void TouchCommand::displayInfo() {
	cout << "Touch creates a file, touch can be invoked ith the command : touch <filename>" << endl;
}