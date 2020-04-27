#pragma once
// Studio 18 - simplefilefactory class declaration goes here

#include <string>
#include <vector>
#include "AbstractFileFactory.h"

using namespace std;

class SimpleFileFactory : public AbstractFileFactory {
public:
	AbstractFile* createFile(string fileName);
};