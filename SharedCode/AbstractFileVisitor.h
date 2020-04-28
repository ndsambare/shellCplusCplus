#pragma once
// declaration of the file visitor interface here
using namespace std;

class ImageFile;
class TextFile;

class AbstractFileVisitor {
public:
	virtual void visit_ImageFile(ImageFile* imgfile) = 0;
	virtual void visit_TextFile(TextFile* txtfile) = 0;
};