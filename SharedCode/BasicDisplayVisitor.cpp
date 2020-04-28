// definitions of basic display visitor here

#include "BasicDisplayVisitor.h"
#include <iostream>


void BasicDisplayVisitor::visit_ImageFile(ImageFile* imgfile) {
	int sizeOfChar = imgfile->getImageSize();
	vector<char> vec = imgfile->read();
	for (int i = sizeOfChar - 1; i >= 0; i--) {
		for (int j = 0; j < sizeOfChar; j++) {
			int index = (sizeOfChar * i) + j;
			cout << vec.at(index);
		}
		cout << endl; 
	}
}
void BasicDisplayVisitor::visit_TextFile(TextFile* txtfile) {
	vector<char> vec = txtfile->read();
	for (char character : vec) {
		cout << character;
	}
}