#include "CommandPrompt.h"
#include <iterator>
#include <sstream>

CommandPrompt::CommandPrompt() {
	this->afs = nullptr;
	this->aff = nullptr;
}

void CommandPrompt::setFileSystem(AbstractFileSystem* inputAFS) {
	this->afs = inputAFS;
}
void CommandPrompt::setFileFactory(AbstractFileFactory* inputAFF) {
	this->aff = inputAFF;
}
int CommandPrompt::addCommand(string input, AbstractCommand* command) {
	size_t initialSize = commandMap.size();
	commandMap.insert(pair<string,AbstractCommand*>(input,command));
	if (initialSize == commandMap.size()) {
		return notAddedMap;
	}
	else {
		return success;
	}
}
int CommandPrompt::run() {
	while (1) {
		string command = prompt();
		if (command == "q") {
			return quit;
		}
		else if (command == "help") {
			listCommands();
		}
		else {
			//check if one word
			bool oneWord = true;
			for (char& c : command) {
				if (c == ' ') {
					oneWord = false;
					break;
				}
			}
			if (oneWord == true) {
				commandMap[command]->execute("");
			}
			else {
				istringstream iss(command);
				string firstCommand, secondCommand;
				iss >> firstCommand >> secondCommand;
				if (firstCommand == "help") {
					//iss >> secondCommand;
					bool find = false;
					for (const auto& pair : commandMap) {
						if (secondCommand == pair.first) {
							pair.second->displayInfo();
							find = true;
							break;
						}
					}
					if (find == false) {
						cout << "Command does not exist." << endl;
					}
				}
				else {
					for (const auto& pair : commandMap) {
						if (firstCommand == pair.first) {
							int index;
							for (int i = 0; i < command.size(); i++) {
								if (command[i] == ' ') {
									index = i;
									break;
								}
							}
							command.erase(0, (index+1));
							pair.second->execute(command);
						}
					}
				}
			}
		}
	}
}

void CommandPrompt::listCommands() {
	for (const auto& pair : commandMap) {
		cout << pair.first;
	}
}
string CommandPrompt::prompt() {
	string command;
	cout << endl;
	cout << "$  ";
	getline(cin, command);
	cout << "test" << endl;
	return command;
}