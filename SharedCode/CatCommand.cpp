#include "CatCommand.h"
#include <sstream>

CatCommand::CatCommand(AbstractFileSystem* afsInput) {
	this->afs = afsInput;
}

int CatCommand::execute(string command) {
	istringstream iss(command);
	string fileName, appendCheck;
	iss >> fileName >> appendCheck;
	AbstractFile* file = afs->openFile(fileName);
	if (file == nullptr) {
		return fileDoesNotExist;
	}
	vector<char> vec;
	if (appendCheck == "-a") {
		for (char c : file->read()) {
			if (c == '\n') {
				cout << endl;
			}
			else {
				cout << c;
			}
		}
		//vec.push_back('\n');
	}
	bool save;
	bool first = true;
	while (1) {
		string input;
		getline(cin, input);
		if (input == ":q") {
			save = false;
			break;
		}
		if (input == ":wq") {
			save = true;
			break;
		}
		if (first == false) {
			vec.push_back('\n');
		}
		for (char c : input) {
			vec.push_back(c);
		}
		first = false;
	}
	int result;
	if (save == true) {
		if (appendCheck == "-a") {
			result = file->append(vec);
		}
		else {
			result = file->write(vec);
		}
	}
	else {
		result = Succ;
	}
	afs->closeFile(file);
	return result;
}
void CatCommand::displayInfo() {
	cout << "Enter data you would like to write to the file. Enter :wq to save and quit, enter :q to exit without saving." << endl;
}