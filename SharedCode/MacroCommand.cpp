#pragma once
#include "MacroCommand.h"
#include "AbstractParsingStrategy.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>


	MacroCommand::MacroCommand(AbstractFileSystem* afsInput) {
		this->afs = afsInput;
	}

	int MacroCommand::execute(string command) {
		//Parsing Strategy will return a string here
		vector<string> commands = strat->parse(command); 


			 for (int i = 0; i < commands.size(); i++) {
				 if (commandVec.at(i)->execute(commands.at(i)) == Succ) {
				 }
				 else {
					 return nullPointer;
				 }
		  }
			 return Succ; 
	}
	void MacroCommand::displayInfo() {
		cout <<  "These are MacroCommands, macro command: rename can be invoked ith the command : rn" << endl;
	}

	void MacroCommand::addCommand(AbstractCommand* absCommand) {
		this->commandVec.push_back(absCommand);

	}

	void MacroCommand::setParseStrategy(AbstractParsingStrategy* parseStrat) {
		strat = parseStrat;
	}
