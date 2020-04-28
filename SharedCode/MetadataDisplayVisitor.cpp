// definitions of metadata visitor here

#include "MetadataDisplayVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"
#include <iostream>

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* imgfile) {
	//print file name
	cout << imgfile->getName() << endl;
	//print file size
	cout << imgfile->getSize() << endl;
	//print file type
	cout << "image" << endl;
}
void MetadataDisplayVisitor::visit_TextFile(TextFile* txtfile) {
	//print file name
	cout << txtfile->getName() << endl;
	//print file size
	cout << txtfile->getSize() << endl;
	//print file type
	cout << "text" << endl;
}