#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class TouchCommand : public AbstractCommand {
private:
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
public:
	TouchCommand(AbstractFileSystem*, AbstractFileFactory*);
	~TouchCommand() = default;
	int execute(string command);
	void displayInfo();
};