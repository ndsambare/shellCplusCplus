#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "Common.h"
#include <iostream>
#include <string>
#include <algorithm>

class CommandTest : public AbstractCommand {
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
public:
	CommandTest(AbstractFileSystem*, AbstractFileFactory*);
	virtual ~CommandTest() = default;
	virtual int execute(std::string, std::string);
	virtual void displayInfo();
};