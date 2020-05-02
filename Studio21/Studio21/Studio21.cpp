// Studio21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <sstream>
#include "../../SharedCode/TextFile.h"
#include "../../SharedCode/ImageFile.h"
#include "../../SharedCode/SimpleFileFactory.h"
#include "../../SharedCode/SimpleFileSystem.h"
#include "../../SharedCode/BasicDisplayVisitor.h"
#include "../../SharedCode/MetadataDisplayVisitor.h"
#include "../../SharedCode/PasswordProxy.h"
#include "../../SharedCode/TouchCommand.h"
#include "../../SharedCode/CommandPrompt.h"
#include "../../SharedCode/CommandTest.h"
#include "..//..//SharedCode/LSCommand.h"
#include "..//..//SharedCode/RemoveCommand.h"
#include "..//..//SharedCode/CatCommand.h"
#include "..//..//SharedCode/DSCommand.h"
#include "..//..//SharedCode/CopyCommand.h"

int main()
{
	AbstractFileSystem* sfs = new SimpleFileSystem();
	AbstractFileFactory* sff = new SimpleFileFactory();
	// ADD FILES
	string filename = "file.txt";
	AbstractFile* file = sff->createFile(filename);
	vector<char> v = { 'f','o','o' };
	sfs->addFile(filename, file);
	sfs->openFile("file.txt");
	file->write(v);
	sfs->closeFile(file);
	AbstractCommand* cc = new CatCommand(sfs);
	AbstractCommand* ls = new LSCommand(sfs);
	AbstractCommand* ds = new DisplayCommand(sfs);
	AbstractCommand* cp = new CopyCommand(sfs);
	AbstractCommand* touch = new TouchCommand(sfs, sff);
	CommandPrompt* cPrompt = new CommandPrompt();
	cPrompt->setFileFactory(sff);
	cPrompt->setFileSystem(sfs);
	cPrompt->addCommand("cat", cc);
	cPrompt->addCommand("ls", ls);
	cPrompt->addCommand("ds", ds);
	cPrompt->addCommand("cp", cp);
	cPrompt->addCommand("touch", touch);
	cPrompt->run();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
