#include "PasswordProxy.h"
#include <iostream>

PasswordProxy::PasswordProxy(AbstractFile* p, string pass) {
	this->filePointer = p;
	this->password = pass;
}

PasswordProxy::~PasswordProxy() {
	delete filePointer;
}

string PasswordProxy::passwordPrompt() {
	string userPassword;
	cin >> userPassword;
	return userPassword;
}
vector<char> PasswordProxy::read() {
	string inputPassword = passwordPrompt();
	vector<char> vec;
	if (inputPassword == password) {
		vec = filePointer->read();
	}
	return vec;
}
int PasswordProxy::write(vector<char> c) {
	string inputPassword = passwordPrompt();
	if (inputPassword == password) {
		return filePointer->write(c);
	}
	else {
		return wrongPass;
	}
}
string PasswordProxy::getName() {
	return filePointer->getName();
}
int PasswordProxy::append(vector<char> c) {
	string inputPassword = passwordPrompt();
	if (inputPassword == password) {
		return filePointer->append(c);
	}
	else {
		return wrongPass;
	}
}
unsigned int PasswordProxy::getSize() {
	return filePointer->getSize();
}
void PasswordProxy::accept(AbstractFileVisitor* visitor) {
	string inputPassword = passwordPrompt();
	if (inputPassword == password) {
		filePointer->accept(visitor);
	}
}

AbstractFile* PasswordProxy::clone(string newFileName) {
	AbstractFile* test = filePointer->clone(newFileName);
	PasswordProxy* newProxy = new PasswordProxy(test,password);
	return newProxy;
}