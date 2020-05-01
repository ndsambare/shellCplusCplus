#pragma once

#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"

using namespace std;

class CatCommand : public AbstractCommand {
private:
	AbstractFileSystem* afs;
public:
	CatCommand(AbstractFileSystem*);
	~CatCommand() = default;
	int execute(string command);
	void displayInfo();
};
