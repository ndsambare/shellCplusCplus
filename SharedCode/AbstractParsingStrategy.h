#pragma once
#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"
#include <string>
#include <vector>

using namespace std;

class AbstractParsingStrategy {

public:
	virtual vector<string> parse(string parseString) = 0;
};
