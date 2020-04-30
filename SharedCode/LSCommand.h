#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class LSCommand : public AbstractCommand {
private:
	AbstractFileSystem* afs;
	
public:
	LSCommand(AbstractFileSystem*);
	~LSCommand() = default;
	int execute(string command);
	void displayInfo();
};
