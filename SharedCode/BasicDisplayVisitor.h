#pragma once
// declaration of BasicDisplayVisitor here
#include "AbstractFileVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"
#include <vector>


using namespace std;

class BasicDisplayVisitor : public AbstractFileVisitor {
public:
	virtual void visit_ImageFile(ImageFile* imgfile);
	virtual void visit_TextFile(TextFile* txtfile);
};