#include "RemoveCommand.h"

#include <iterator>
#include "SimpleFileSystem.h"


RemoveCommand::RemoveCommand(AbstractFileSystem* afsInput) {
	this->afs = afsInput;

}

int RemoveCommand::execute(string command) {
	
	if (afs->deleteFile(command) == Succ) {
		return Succ;
	}
	else {
		return fileDoesNotExist; 
	}
	
}
void RemoveCommand::displayInfo() {
	cout << "Touch creates a file, touch can be invoked ith the command : rm <filename>" << endl;
}