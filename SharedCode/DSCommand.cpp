#include "DSCommand.h"
#include "BasicDisplayVisitor.h"
#include "MetadataDisplayVisitor.h"
#include <sstream>

DisplayCommand::DisplayCommand(AbstractFileSystem* afsInput) {
	this->afs = afsInput;
}

int DisplayCommand::execute(string command) {
	istringstream iss(command);
	string fileName, formatCheck;
	iss >> fileName >> formatCheck;
	AbstractFile* file = afs->openFile(fileName);
	if (file == nullptr) {
		return fileDoesNotExist;
	}
	if (formatCheck == "-d") {
		for (char c : file->read()) {
			cout << c;
		}
		cout << '\n';
	}
	
	else {
		AbstractFileVisitor* bdv = new BasicDisplayVisitor();
		file->accept(bdv);
	}
	afs->closeFile(file);
	return Succ;
}
void DisplayCommand::displayInfo() {
	cout << "Display the contents of a file using display <filename> [-d]" << endl;
}