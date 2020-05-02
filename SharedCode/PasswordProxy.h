#pragma once

#include "AbstractFile.h"

using namespace std;

class PasswordProxy : public AbstractFile {
private:
	AbstractFile* filePointer;
	string password;
public:
	PasswordProxy(AbstractFile* p, string pass);
	~PasswordProxy();
	vector<char> read();
	int write(vector<char> c);
	string getName();
	int append(vector<char> c);
	unsigned int getSize();
	void accept(AbstractFileVisitor* visitor);
	AbstractFile* clone(string);
protected:
	string passwordPrompt();
};