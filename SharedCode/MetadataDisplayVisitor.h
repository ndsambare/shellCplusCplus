#pragma once
// declaration of MetadataDisplayVisitor here
#include "AbstractFileVisitor.h"

using namespace std;

class MetadataDisplayVisitor : public AbstractFileVisitor {
public:
	virtual void visit_ImageFile(ImageFile* imgfile);
	virtual void visit_TextFile(TextFile* txtfile);
};