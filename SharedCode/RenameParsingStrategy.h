#pragma once
#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"
#include <string>
#include <vector>
#include "AbstractParsingStrategy.h"

using namespace std;

class RenameParsingStrategy : public AbstractParsingStrategy {

public:
	virtual vector<string> parse(string parseString);
};

