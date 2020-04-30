// definitions of metadata visitor here

#include "MetadataDisplayVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"
#include <iostream>

void MetadataDisplayVisitor::visit_ImageFile(ImageFile* imgfile) {
	//print file name
	cout << imgfile->getName() <<" ";
	//print file type
	cout << "image" << " ";
	//print file size
	cout << imgfile->getSize() << endl;
	
}
void MetadataDisplayVisitor::visit_TextFile(TextFile* txtfile) {
	//print file name
	cout << txtfile->getName() << " ";
	//print file type
	cout << "text" << " ";
	//print file size
	cout << txtfile->getSize() << endl;
	
}