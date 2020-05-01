// definition of ImageFile class here
#include "AbstractFile.h"
#include "ImageFile.h"
#include <vector>
#include <string>

#include <iostream>



ImageFile::ImageFile(string name) {
	this->fileName = name;
	this->imageSize = 0;
}
unsigned int ImageFile::getSize() {
	unsigned int sizeBro = fileContent.size();
	return sizeBro; 
}

string ImageFile::getName() {
	string nameBro = this->fileName;
	return nameBro; 
}

int ImageFile::write(vector<char> c) {
	//look at last char and use it to set the size member variable
	this->imageSize = c[c.size() - 1];
	//gets the integer value by subtracting 48
	int sizeofInt = this->imageSize - '0';
	if (c.size() - 1 != (sizeofInt * sizeofInt)) {
		//if there is a size mismatch
		return sizeMisMatch;
	}
	vector<char> correctVec;
	unsigned int lengthOfVec = c.size(); 
	for (int i = 0; i < lengthOfVec -1; i++) {
		//checks to see if the character is not either an X or a space
		if (c[i] != 'X' && c[i] != ' ') {
				this->imageSize = 0;
				vector<char> reset;
				this->fileContent = reset;
				return IncorrectChar;
		}
		//only if the correct input is there will it ever push back
		correctVec.push_back(c[i]);
	}

	this->fileContent = correctVec;
	return Success;
}

int ImageFile::append(vector <char> a) {
	return appendNotSupported; 
}


 int ImageFile::coordinateToIndex(unsigned int x, unsigned int y) {
	unsigned int size = this->imageSize - '0';
	int index = (size * y) + x;
	return index; 
}

vector<char> ImageFile::read() {
	int sizeOfChar = this->imageSize - '0'; 
	//vector<char> vec;
	/*for (int i = sizeOfChar - 1; i >= 0; i--) {
		for (int j = 0; j < sizeOfChar; j++) {
			int index = coordinateToIndex(j, i);
			vec.push_back(fileContent.at(index));
			//cout << fileContent.at(index);
		}
		//vec.push_back('\n');
	}*/
	return fileContent;
}

int ImageFile::getImageSize() {
	int sizeOfChar = this->imageSize - '0';
	return sizeOfChar;
}