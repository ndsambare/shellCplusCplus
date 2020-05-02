#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class CopyCommand : public AbstractCommand {
private:
	AbstractFileSystem* afs;
public:
	CopyCommand(AbstractFileSystem*);
	~CopyCommand() = default;
	int execute(string command);
	void displayInfo();
};
