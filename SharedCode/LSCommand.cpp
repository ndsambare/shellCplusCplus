#include "LSCommand.h"
#include "SimpleFileSystem.h"
#include <iterator>
#include "MetadataDisplayVisitor.h"

LSCommand::LSCommand(AbstractFileSystem* afsInput) {
	this->afs = afsInput;
	
}

int LSCommand::execute(string command) {
	if (command == "") {
		set<string> fileNames = afs->getFileNames();
		int counter = 0;
		set<string>::iterator it;
		for (it = fileNames.begin(); it != fileNames.end(); ++it) {
		
			cout << *it<< " ";
			if (counter % 2 == 1) {
				cout << endl;
			}
			counter++;
		}
	}
	else if (command == "-m") {
		set<string> fileNames = afs->getFileNames(); 
		for (string s : fileNames) {
			AbstractFile* file = afs->openFile(s);
			MetadataDisplayVisitor* visitor = new MetadataDisplayVisitor(); 
			file->accept(visitor);
			delete visitor; 
			afs->closeFile(file);

		}
	}
	return Succ; 
}
void LSCommand::displayInfo() {
	cout << "Touch creates a file, touch can be invoked ith the command : ls [-m]" << endl;
}