#pragma once
#pragma once


#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"
#include "SimpleFileSystem.h"

using namespace std;

class RemoveCommand  {
private:
	AbstractFileSystem* afs;

public:
	RemoveCommand(AbstractFileSystem*);
	~RemoveCommand() = default;
	int execute(string command);
	void displayInfo();
};
