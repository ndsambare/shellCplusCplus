//  Define the TextFile class here

#include <vector>
#include <string>
#include <iostream>
#include "TextFile.h"
#include "AbstractFile.h"
using namespace std;

TextFile::TextFile(string name) {
	this->fileName = name;
}

unsigned int TextFile::getSize() {
	return this->fileContent.size();
}

string TextFile::getName() {
	string nameString = this->fileName;
	return nameString; 
}

int TextFile::write(vector<char> c) {
	this->fileContent = c;
	//return 0 means it was successful
	return Success;
}

int TextFile::append(vector<char> c) {
	for (char character : c) {
		this->fileContent.push_back(character);
	}
	//returning 0 means it was successful
	return 0;
}

vector<char> TextFile::read() {
	vector<char> vec;
	for (char character : this->fileContent) {
		vec.push_back(character);
		//cout << character;
	}
	return vec;
}

AbstractFile* TextFile::clone(string newFileName) {
	TextFile* newFile = new TextFile(*this);
	newFile->fileName = newFileName;
	return newFile;
}