// Studio18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../..//SharedCode/AbstractFileFactory.h"
#include "../..//SharedCode/SimpleFileFactory.h"
#include "../..//SharedCode/AbstractFileSystem.h"
#include "../..//SharedCode/SimpleFileSystem.h"
#include "../..//SharedCode/TextFile.h"
#include "../..//SharedCode/ImageFile.h"



int main()
{
	AbstractFileSystem* afs = new SimpleFileSystem;
	AbstractFileFactory* aff = new SimpleFileFactory;
	vector<char> vec { 'n' , 'i' , 'c', 'e'};
	AbstractFile* file = aff->createFile("nice.txt");
	AbstractFile* file2 = aff->createFile("nice2.txt");
	afs->addFile("nice.txt", file2);
	afs->addFile("nice.txt", file2);
	afs->openFile("nice.txt");
	afs->openFile("nice2.txt");
	file->write(vec);
	file->read();
	file2->write(vec);
	file2->read();
}
