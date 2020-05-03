#pragma once

#include "AbstractCommand.h"
#include "AbstractParsingStrategy.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

// declaration of SimpleFileSystem class goes here
class MacroCommand : public AbstractCommand {
public:
	  int execute(string command);
    void displayInfo();
	MacroCommand(AbstractFileSystem*);
	 ~MacroCommand() = default;
	void addCommand(AbstractCommand* absCommand); 
	void setParseStrategy(AbstractParsingStrategy* parseStrat);

private:
	AbstractFileSystem* afs;
	vector<AbstractCommand*> commandVec; 
	AbstractParsingStrategy* strat; 
};