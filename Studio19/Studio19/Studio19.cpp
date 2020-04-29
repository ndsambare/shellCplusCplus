// Studio19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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

int main()
{
	AbstractFileSystem* sfs = new SimpleFileSystem();
	AbstractFileFactory* sff = new SimpleFileFactory();
	CommandPrompt* cp = new CommandPrompt;
	cp->setFileSystem(sfs);
	cp->setFileFactory(sff);
	// ADD COMMAND
	CommandTest* ct = new CommandTest(sfs);
	string commandname = "test";
	//Assert::AreEqual(cp->addCommand(commandname, ct), 0);
	// REDIRECT COUT STREAM
	streambuf* backup_out;
	backup_out = cout.rdbuf();
	stringstream ss_out;
	cout.rdbuf(ss_out.rdbuf());
	// REDIRECT CIN STREAM
	streambuf* backup_in;
	backup_in = cin.rdbuf();
	stringstream ss_in;
	cin.rdbuf(ss_in.rdbuf());
	// MIMIC USER INPUT
	string input = "test foo moo\nq\n";
	ss_in << input;
	int response = cp->run();
	//Assert::AreNotEqual(response, 0);
	string word;
	std::vector<string> printedWords;
	while (ss_out >> word) {
		printedWords.push_back(word);
	}
	// EXPECTATION -- ALL PARAMETERS SHOULD BE PRINTED TO COUT
	std::vector<string>::iterator it1;
	string expectedOutput = "foo:moo";
	it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
	bool notEqual1 = it1 == printedWords.end();
	//Assert::IsFalse(notEqual1);
	// ASSIGN COUT BACK TO STDOUT
	cout.rdbuf(backup_out);
	// ASSIGN CIN BACK TO STDIN
	cin.rdbuf(backup_in);

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
