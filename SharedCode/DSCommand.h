#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class DisplayCommand : public AbstractCommand {
private:
	AbstractFileSystem* afs;
public:
	DisplayCommand(AbstractFileSystem*);
	~DisplayCommand() = default;
	int execute(string command);
	void displayInfo();
};
#pragma once
