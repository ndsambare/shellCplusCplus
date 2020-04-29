#pragma once
#include <map>
#include <string>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

using namespace std;

enum commandResults {
	success, notAddedMap, quit
};

class CommandPrompt  {
private:
	map<string, AbstractCommand*> commandMap;
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
public:
	CommandPrompt();
	~CommandPrompt() = default;
	void setFileSystem(AbstractFileSystem*);
	void setFileFactory(AbstractFileFactory*);
	int addCommand(string, AbstractCommand*);
	int run();
protected:
	void listCommands();
	string prompt();
};