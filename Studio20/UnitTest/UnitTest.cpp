#include "pch.h"
#include "CppUnitTest.h"
#define protected public
#include "../../SharedCode/TextFile.cpp"
#include "../../SharedCode/ImageFile.cpp"
#include "../../SharedCode/SimpleFileFactory.cpp"
#include "../../SharedCode/SimpleFileSystem.cpp"
#include "../../SharedCode/BasicDisplayVisitor.cpp"
#include "../../SharedCode/MetadataDisplayVisitor.cpp"
#include "../../SharedCode/DirectoryFile.cpp"
#include "../../SharedCode/HierarchicalFileSystem.cpp"
#undef protected


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(textFile)
	{
	public:

		TEST_METHOD(contstructor)  // checks that the file is initialized with proper name and size, expects size to be 0, the name to match the input to the constructor, and the parent to be nullptr
		{
			std::string fileName = "FileName.txt";
			unsigned int fileSize = 0;
			TextFile t(fileName);
			Assert::AreEqual(t.getName(), fileName);
			Assert::AreEqual(t.getSize(), fileSize);
			bool isnull = t.getParent() == nullptr;
			Assert::IsTrue(isnull);
		}
		TEST_METHOD(write) // tests write, expects that the function returns success and that the size of the file is updated correctly
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(t.write(v), 0);
			Assert::AreEqual(t.getSize(), static_cast<unsigned int>(v.size()));

		}
		TEST_METHOD(append) // tests append, expects the write and append functions to return 0 and the size of the file to update correctly
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(t.write(v), 0);
			unsigned int fileSize = t.getSize();
			Assert::AreEqual(t.append(v), 0);
			Assert::AreEqual(t.getSize(), static_cast<unsigned int>(fileSize + v.size()));

		}
		TEST_METHOD(read) // tests that the read function outputs the contents of the file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(t.write(v), 0);
			std::vector<char> contents = t.read();
			Assert::AreEqual(t.getSize(), v.size());
			Assert::AreEqual(contents.size(), v.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(v[i], contents[i]);
			}
		}
		TEST_METHOD(readWithAppend) // tests that read also works with appending to a file
		{
			std::string fileName = "FileName.txt";
			TextFile t(fileName);
			std::vector<char> v = { 'h', 'i' };
			Assert::AreEqual(t.write(v), 0);
			Assert::AreEqual(t.append(v), 0);
			std::vector<char> newExpectedV = { 'h', 'i',  'h', 'i' };
			std::vector<char> contents = t.read();
			Assert::AreEqual(t.getSize(), static_cast<unsigned int>(newExpectedV.size()));
			Assert::AreEqual(contents.size(), newExpectedV.size());
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(newExpectedV[i], contents[i]);
			}
		}
		TEST_METHOD(addChildValid) { // checks that addChild returns an error for a textfile
			AbstractFile* parent = new TextFile("TestParent.txt");
			AbstractFile* child = new TextFile("TestChild.txt");
			Assert::AreNotEqual(parent->addChild(child), 0);
		}
		TEST_METHOD(removeChildValid) { // checks removeChild returns an error for a textfile
			AbstractFile* parent = new TextFile("TestParent.txt");
			AbstractFile* child = new TextFile("TestChild.txt");
			Assert::AreNotEqual(parent->removeChild(child->getName()), 0);
		}
		TEST_METHOD(getChildValid) { // checks getChild returns a nullptr for a textfile
			AbstractFile* parent = new TextFile("TestParent.txt");
			AbstractFile* child = new TextFile("TestChild.txt");
			bool isNull = parent->getChild(child->getName()) == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(getSetParentValid) { // checks that when you set a textfile's parent, getParent returns what you first set it to be
			AbstractFile* parent = new TextFile("TestParent.txt");
			AbstractFile* child = new TextFile("TestChild.txt");
			child->setParent(parent);
			bool same = child->getParent() == parent;
			Assert::IsTrue(same);
		}
	};
	TEST_CLASS(imageFile)
	{
	public:

		TEST_METHOD(contstructor) // checks that the file is initialized with proper name and size, expects size to be 0, the name to match the input to the constructor, and the parent to be nullptr
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			Assert::AreEqual(t.getName(), fileName);
			Assert::AreEqual(t.getSize(), fileSize);
			bool isnull = t.getParent() == nullptr;
			Assert::IsTrue(isnull);
		}
		TEST_METHOD(writeValid) // tests write with a valid vector input, expects write to return success, and the size of the contents to be equal to that of the input vector -1 (for the last index that is removed
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(t.write(v), 0);
			Assert::AreEqual(t.getSize(), static_cast<unsigned int>(v.size() - 1));
		}
		TEST_METHOD(writeSizeMismatch) // tests write with a size mismatch in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '4' };
			Assert::AreNotEqual(t.write(v), 0); // non-zero error returned
			Assert::AreEqual(t.getSize(), fileSize); // contents not added
		}
		TEST_METHOD(writeInvalidPixel) // tests write with an invalid pixel in the input vector, expects write to return a non-zero value and the size of the contents to remain 0
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert::AreNotEqual(t.write(v), 0);
			Assert::AreEqual(t.getSize(), fileSize); // contents not added
		}
		TEST_METHOD(appendInvalid) // tests that append returns a non-zero value (can't append to an image)
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'Y', ' ', 'X',' ', 'X', '3' };
			Assert::AreNotEqual(t.append(v), 0); // can't append to image
		}
		TEST_METHOD(read) // tests that read returns the contents that are written to the file
		{
			std::string fileName = "FileName.img";
			ImageFile t(fileName);
			std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
			Assert::AreEqual(t.write(v), 0);
			std::vector<char> contents = t.read();
			Assert::AreEqual(contents.size(), v.size() - 1);
			for (size_t i = 0; i < contents.size(); ++i) {
				Assert::AreEqual(contents[i], v[i]);
			}
		}
		TEST_METHOD(addChildValid) { // checks addChild returns an error value for an image file
			AbstractFile* parent = new ImageFile("TestParent.img");
			AbstractFile* child = new ImageFile("TestChild.img");
			Assert::AreNotEqual(parent->addChild(child), 0);
		}
		TEST_METHOD(removeChildValid) { // checks removeChild returns an error value for an image file
			AbstractFile* parent = new ImageFile("TestParent.img");
			AbstractFile* child = new ImageFile("TestChild.img");
			Assert::AreNotEqual(parent->removeChild(child->getName()), 0);
		}
		TEST_METHOD(getChildValid) { // checks getChild returns a nullptr for an image file
			AbstractFile* parent = new ImageFile("TestParent.img");
			AbstractFile* child = new ImageFile("TestChild.img");
			bool isNull = parent->getChild(child->getName()) == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(getSetParentValid) { // checks that if you set a parent, getParent will return the same file you set it to be
			AbstractFile* parent = new ImageFile("TestParent.img");
			AbstractFile* child = new ImageFile("TestChild.img");
			child->setParent(parent);
			bool same = child->getParent() == parent;
			Assert::IsTrue(same);
		}
	};
	TEST_CLASS(simpleFileSystem)
	{
	public:

		TEST_METHOD(addValid) // adds two different files to the system, expects success as return value both times
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* txt = sff.createFile("FileName.txt");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert::AreEqual(sfs.addFile(txt->getName(), txt), 0);
		}
		TEST_METHOD(addNullFile) // adds a nullptr to the filesystem, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			ImageFile* img = nullptr;
			Assert::AreNotEqual(sfs.addFile("FileName.img", img), 0);
		}
		TEST_METHOD(addFileAlreadyExists) // adds the same file twice, the first time should return success, the second time should return a non-zero value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert::AreNotEqual(sfs.addFile(img->getName(), img), 0);
		}
		TEST_METHOD(deleteValid) // deletes a valid file (a file that exists and is not open), expects 0 as a return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert::AreEqual(sfs.deleteFile(img->getName()), 0);
		}
		TEST_METHOD(deleteFileDoesNotExist) // deletes a file that has not been added, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreNotEqual(sfs.deleteFile(img->getName()), 0);
		}
		TEST_METHOD(openValid) //  opens a valid file that exists and is not already open, expect to see the same file returned
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*res1);
			Assert::IsTrue(sameAddress);
		}
		TEST_METHOD(openFileNotAdded) // opens a file that has not been added, expects a null pointer
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			AbstractFile* res1 = sfs.openFile(img->getName());
			bool isNull = res1 == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(openAlreadyOpenedFile) // opens a file twice, the first time should return the same file, the second time should return nullptr
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			AbstractFile* firstOpen = sfs.openFile(img->getName());
			bool sameAddress = &(*img) == &(*firstOpen);
			Assert::IsTrue(sameAddress);
			AbstractFile* secondOpen = sfs.openFile(img->getName());
			bool isNull = secondOpen == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(closeValid) // closes a file that has been added and opened, expect success
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			sfs.addFile(img->getName(), img);
			sfs.openFile(img->getName());
			int res1 = sfs.closeFile(img);
			Assert::AreEqual(res1, 0);
		}
		TEST_METHOD(closeNotOpen) // closes a file that has been added but not opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreEqual(sfs.addFile(img->getName(), img), 0);
			Assert::AreNotEqual(sfs.closeFile(img), 0);
		}
		TEST_METHOD(closeNotAdded) // closes a file that has not been added or opened, expects a non-zero return value
		{
			SimpleFileSystem sfs;
			SimpleFileFactory sff;
			AbstractFile* img = sff.createFile("FileName.img");
			Assert::AreNotEqual(sfs.closeFile(img), 0);
		}
	};
	TEST_CLASS(simpleFileFactory) {
public:
	TEST_METHOD(createFileValid) // creates two files by calling create on the file factory, the calls should return the new file objects that are both not null
	{
		SimpleFileFactory sff;
		AbstractFile* res1 = sff.createFile("FileName.img");
		bool isNull1 = res1 == nullptr;
		Assert::IsFalse(isNull1);
		AbstractFile* res2 = sff.createFile("FileName.txt");
		bool isNull2 = res2 == nullptr;
		Assert::IsFalse(isNull2);
	}
	TEST_METHOD(createUnknownExtension) // when a bad extension is passed, the factory should pass back a nullptr
	{
		SimpleFileFactory sfs;
		AbstractFile* res1 = sfs.createFile("FileName.bla");
		bool isNull = res1 == nullptr;
		Assert::IsTrue(isNull);
	}
	};
	TEST_CLASS(basicDisplayVisitor) {
public:
	TEST_METHOD(visitTextFile) { // tests output of basic display visitor for a text file, expects the contents of the file
		std::string fileName = "FileName.txt";
		TextFile t(fileName);
		std::vector<char> v = { 'h', 'i' };
		int resWrite = t.write(v);
		// REDIRECT STD STREAM
		streambuf* backup;
		backup = cout.rdbuf();
		stringstream ss;
		cout.rdbuf(ss.rdbuf());
		AbstractFileVisitor* bdv = new BasicDisplayVisitor;
		t.accept(bdv);
		string wordShouldBe = "hi";
		string word;
		ss >> word;
		// ASSIGN COUT BACK TO STDOUT
		cout.rdbuf(backup);
		Assert::AreEqual(word, wordShouldBe);
		Assert::AreEqual(resWrite, 0);
	}
	TEST_METHOD(visitImageFile) { // tests the output the basic display visitor for an image file, expects 5 Xs
		string fileName = "FileName.img";
		ImageFile t(fileName);
		vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
		Assert::AreEqual(t.write(v), 0);
		// REDIRECT STD STREAM
		streambuf* backup;
		backup = cout.rdbuf();
		stringstream ss;
		cout.rdbuf(ss.rdbuf());
		AbstractFileVisitor* bdv = new BasicDisplayVisitor;
		t.accept(bdv);
		string outputShouldBe = "X";
		string word;
		int count = 0;
		while (ss >> word) { // no skip ws -- wont skip white space! would have to extract one character at a time
			Assert::AreEqual(word, outputShouldBe);
			++count;
		}
		// ASSIGN COUT BACK TO STDOUT
		cout.rdbuf(backup);
		Assert::AreEqual(count, 5);
	}
	};
	TEST_CLASS(metadataDisplayVisitor) {
public:
	TEST_METHOD(visitTextFile) { // tests the output of the metadata display visitor for a text file, expects the filename, type and size to be included in the print statement
		std::string fileName = "FileName.txt";
		TextFile t(fileName);
		std::vector<char> v = { 'h', 'i' };
		Assert::AreEqual(t.write(v), 0);
		// REDIRECT STD STREAM
		streambuf* backup;
		backup = cout.rdbuf();
		stringstream ss;
		cout.rdbuf(ss.rdbuf());
		AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
		t.accept(bdv);
		string word;
		std::vector<string> printedWords;
		while (ss >> word) {
			printedWords.push_back(word);
		}
		std::vector<string>::iterator it1;
		std::vector<string>::iterator it2;
		std::vector<string>::iterator it3;
		it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
		bool notEqual1 = it1 == printedWords.end();
		Assert::IsFalse(notEqual1);
		it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
		bool notEqual2 = it2 == printedWords.end();
		Assert::IsFalse(notEqual2);
		it3 = std::find(printedWords.begin(), printedWords.end(), "text");
		bool notEqual3 = it3 == printedWords.end();
		Assert::IsFalse(notEqual3);
		// ASSIGN COUT BACK TO STDOUT
		cout.rdbuf(backup);
	}
	TEST_METHOD(visitImageFile) { // tests the output of the metadata display visitor for an image file, expects the filename, type and size to be included in the output
		std::string fileName = "FileName.img";
		ImageFile t(fileName);
		std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
		Assert::AreEqual(t.write(v), 0);
		// REDIRECT STD STREAM
		streambuf* backup;
		backup = cout.rdbuf();
		stringstream ss;
		cout.rdbuf(ss.rdbuf());
		AbstractFileVisitor* bdv = new MetadataDisplayVisitor;
		t.accept(bdv);
		string word;
		std::vector<string> printedWords;
		while (ss >> word) {
			printedWords.push_back(word);
		}
		std::vector<string>::iterator it1;
		std::vector<string>::iterator it2;
		std::vector<string>::iterator it3;
		it1 = std::find(printedWords.begin(), printedWords.end(), fileName);
		bool notEqual1 = it1 == printedWords.end();
		Assert::IsFalse(notEqual1);
		it2 = std::find(printedWords.begin(), printedWords.end(), to_string(t.getSize()));
		bool notEqual2 = it2 == printedWords.end();
		Assert::IsFalse(notEqual2);
		it3 = std::find(printedWords.begin(), printedWords.end(), "image");
		bool notEqual3 = it3 == printedWords.end();
		Assert::IsFalse(notEqual3);
		// ASSIGN COUT BACK TO STDOUT
		cout.rdbuf(backup);
	}
	};
	TEST_CLASS(directoryFile) { //not tested: destructor, read, getSize, accept
public:
	TEST_METHOD(contstructor) { // checks that the file is initialized with proper name and parent, expects the name to be the same as is passed to the constructor and the parent to initially be a nullptr
		std::string filename = "filename.txt";
		DirectoryFile t(filename);
		Assert::AreEqual(t.getName(), filename);
		bool isnull = t.getParent() == nullptr;
		Assert::IsTrue(isnull);
	}
	TEST_METHOD(writevalid) { // checks the write function, expects an error suggesting you can't write to a directory and contents to be unchanged
		std::string filename = "filename";
		DirectoryFile t(filename);
		std::vector<char> v;
		v.push_back('h');
		v.push_back('i');
		Assert::AreNotEqual(t.write(v), 0);
		Assert::AreEqual(t.getSize(), static_cast<unsigned int>(0));
	}
	TEST_METHOD(appendvalid) {  // checks the append function, expects an error suggesting you can't append to a directory and contents to be unchanged
		std::string filename = "filename.txt";
		DirectoryFile t(filename);
		std::vector<char> v;
		v.push_back('h');
		v.push_back('i');
		Assert::AreNotEqual(t.append(v), 0);
		Assert::AreEqual(t.getSize(), static_cast<unsigned int>(0));
	}
	TEST_METHOD(getChildExists) {  // checks the getChild function, expects f1 to be a child of d when addChild is called, getChild should return the original text file, f1
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		d->addChild(f1);
		AbstractFile* child = d->getChild(filename);
		bool aresame = child == f1;
		Assert::IsTrue(aresame);
	}
	TEST_METHOD(getChildDoesNotExists) { // in this case, we expect the child to not exist since it was never added, therefore we expect getChild to return a nullptr
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		AbstractFile* child = d->getChild(filename);
		bool aresame = child == nullptr;
		Assert::IsTrue(aresame);
	}
	TEST_METHOD(addChildValid) { // checks addChild function, expects addChild to return success and that the child's filename was added to the contents of the directory
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		Assert::AreEqual(d->addChild(f1), 0);
		vector<char> contents = d->read();
		char* searchString = "file1.txt\n";
		auto it = search(contents.begin(), contents.end(), searchString, searchString + strlen(searchString));
		bool same = it == contents.end();
		Assert::IsFalse(same);
		int occurrences = 1;
		while (it != contents.end()) {
			++it;
			it = search(it, contents.end(), searchString, searchString + strlen(searchString));
			if (it != contents.end()) {
				++occurrences;
			}
		}
		Assert::AreEqual(occurrences, 1);
	}
	TEST_METHOD(addChildAlreadyExists) { // checks case when a file is added as a child twice, expects an error from the second add child, but the name should still exist in the contents of the directory (but only 1 time)
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		d->addChild(f1);
		Assert::AreNotEqual(d->addChild(f1), 0);
		vector<char> contents = d->read();
		char* searchString = "file1.txt\n";
		auto it = search(contents.begin(), contents.end(), searchString, searchString + strlen(searchString));
		bool same = it == contents.end();
		Assert::IsFalse(same);
		int occurrences = 1;
		while (it != contents.end()) {
			++it;
			it = search(it, contents.end(), searchString, searchString + strlen(searchString));
			if (it != contents.end()) {
				++occurrences;
			}
		}
		Assert::AreEqual(occurrences, 1);
	}
	TEST_METHOD(removeChildValid) { // checks removeChild function, after the file is added as a child, we expect success when calling removeChild, we also expect the filename to be erased from the contents of the directory
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		d->addChild(f1);
		Assert::AreEqual(d->removeChild(filename), 0);
		vector<char> contents = d->read();
		char* searchString = "file1.txt\n";
		auto it = search(contents.begin(), contents.end(), searchString, searchString + strlen(searchString));
		bool same = it == contents.end();
		Assert::IsTrue(same);
	}
	TEST_METHOD(removeChildDoesNotExist) { // in this case the child we are trying to remove was never added, we expect an error, the contents should not contain the filename we are trying to remove
		std::string directoryname = "files";
		AbstractFile* d = new DirectoryFile(directoryname);
		std::string filename = "file1.txt";
		AbstractFile* f1 = new TextFile(filename);
		Assert::AreNotEqual(d->removeChild(filename), 0);
		vector<char> contents = d->read();
		char* searchString = "file1.txt\n";
		auto it = search(contents.begin(), contents.end(), searchString, searchString + strlen(searchString));
		bool same = it == contents.end();
		Assert::IsTrue(same);
	}
	TEST_METHOD(getSetParentValid) { // checks the get and set parent functions, we should get the same parent that we first set!
		AbstractFile* parent = new DirectoryFile("TestParent");
		AbstractFile* child = new DirectoryFile("TestChild");
		child->setParent(parent);
		bool same = child->getParent() == parent;
		Assert::IsTrue(same);
	}
	};
	TEST_CLASS(hierarchicalFileSystem) { //not tested: constructor, destructor
public:
	TEST_METHOD(parsePathValid) { // checks the parsePath helper function, we expect the function to return the file at the end of the path if the path is valid
		string path = "root/directory1/directory2/filename.txt";
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("directory1");
		AbstractFile* d2 = new DirectoryFile("directory2");
		AbstractFile* file = new TextFile("filename.txt");
		Assert::AreEqual(hfs.addFile("root/directory1", d1), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2", d2), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2/filename.txt", file), 0);
		AbstractFile* returnedFile = hfs.parsePath(path);
		bool areSame = returnedFile == file;
		Assert::IsTrue(areSame);
	}
	TEST_METHOD(parsePathInvalidPathNoRoot) { /// we expect parsePath to return an nullptr if the path is invalid (does not start with root)
		string path = "directory1/directory2/filename.txt";
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("directory1");
		AbstractFile* d2 = new DirectoryFile("directory2");
		AbstractFile* file = new TextFile("filename.txt");
		Assert::AreEqual(hfs.addFile("root/directory1", d1), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2", d2), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2/filename.txt", file), 0);
		AbstractFile* returnedFile = hfs.parsePath(path);
		bool areSame = returnedFile == nullptr;
		Assert::IsTrue(areSame);
	}
	TEST_METHOD(parsePathIsRoot) { // we expect in this case to get the root file back from the parsePath function
		string path = "root";
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("directory1");
		AbstractFile* d2 = new DirectoryFile("directory2");
		AbstractFile* file = new TextFile("filename.txt");
		Assert::AreEqual(hfs.addFile("root/directory1", d1), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2", d2), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2/filename.txt", file), 0);
		AbstractFile* returnedFile = hfs.parsePath(path);
		Assert::AreEqual(returnedFile->getName(), static_cast<string>("root"));
	}
	TEST_METHOD(parsePathInvalidPath) { // we expect a nullptr to be returned, the path being passed to parsePath does not match the filesystem created (directory3 does not exist!)
		string path = "root/directory1/filename.txt";
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("directory1");
		AbstractFile* d2 = new DirectoryFile("directory2");
		AbstractFile* file = new TextFile("filename.txt");
		Assert::AreEqual(hfs.addFile("root/directory1", d1), 0);
		Assert::AreEqual(hfs.addFile("root/directory1/directory2", d2), 0);
		Assert::AreNotEqual(hfs.addFile("root/directory1/directory3/filename.txt", file), 0);
		AbstractFile* returnedFile = hfs.parsePath(path);
		bool areSame = returnedFile == nullptr;
		Assert::IsTrue(areSame);
	}
	TEST_METHOD(openFileValid) { // after a file has been successfully added, we expect that the openFile function will return the same file we added to the given path
		HierarchicalFileSystem hfs;
		DirectoryFile* d1 = new DirectoryFile("files");
		string filepath = "root/files";
		Assert::AreEqual(hfs.addFile(filepath, d1), 0);
		AbstractFile* o1 = hfs.openFile(filepath);
		bool areSame = o1 == d1;
		Assert::IsTrue(areSame);
	}
	TEST_METHOD(openFileDoesNotExist) {  // if the file does not exist at the file path, openFile should return a nullptr (in this case, it is never added)
		HierarchicalFileSystem hfs;
		string filepath = "root/files";
		AbstractFile* o1 = hfs.openFile(filepath);
		bool isNull = o1 == nullptr;
		Assert::IsTrue(isNull);
	}
	TEST_METHOD(openFileAlreadyOpen) {  // if the file is already open, openFile should return a nullptr 
		HierarchicalFileSystem hfs;
		DirectoryFile* d1 = new DirectoryFile("files");
		string filepath = "root/files";
		Assert::AreEqual(hfs.addFile(filepath, d1), 0);
		AbstractFile* o1 = hfs.openFile(filepath);
		bool isNull = o1 == nullptr;
		Assert::IsFalse(isNull);
		AbstractFile* o2 = hfs.openFile(filepath);
		bool isNull2 = o2 == nullptr;
		Assert::IsTrue(isNull2);
	}
	TEST_METHOD(openFileInvalidPath) { // if the file does not exist at the given path (but exists elsewhere), openFile should still return a nullptr
		HierarchicalFileSystem hfs;
		DirectoryFile* d1 = new DirectoryFile("files");
		string filepath = "root/files";
		Assert::AreEqual(hfs.addFile(filepath, d1), 0);
		AbstractFile* o1 = hfs.openFile("root/directory/files");
		bool isNull = o1 == nullptr;
		Assert::IsTrue(isNull);
	}
	TEST_METHOD(closeFileValid) { // if a file is added and opened, we expect closeFile to return success and to be able to successfully call open file again 
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		string filepath = "root/files";
		Assert::AreEqual(hfs.addFile(filepath, d1), 0);
		AbstractFile* returnedFile = hfs.openFile(filepath);
		bool same = returnedFile == d1;
		Assert::IsTrue(same);
		Assert::AreEqual(hfs.closeFile(d1), 0);
		AbstractFile* returnedFile2 = hfs.openFile(filepath);
		same = returnedFile2 == d1;
		Assert::IsTrue(same);
	}
	TEST_METHOD(closeFileNotOpen) { // if the file exists, but is not opened, we expect closeFile to return an error
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		string filepath = "root/files";
		Assert::AreEqual(hfs.addFile(filepath, d1), 0);
		Assert::AreNotEqual(hfs.closeFile(d1), 0);
	}
	TEST_METHOD(deleteFileValid) { // if a file is properly added and then deleted, we expect it to be removed as a child from its parent
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreEqual(hfs.deleteFile(filepath), 0);
		Assert::AreEqual(d1->getParent()->getName(), static_cast<string>("root"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == nullptr;
		Assert::IsTrue(same);
		// additional check that the file has been removed from the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		bool isNull = ret == nullptr;
		Assert::IsTrue(isNull);
	}
	TEST_METHOD(deleteInvalidPath) { // if the path given to delete the file is invalid, then we expect the parent/child relationship to remain the same
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreNotEqual(hfs.deleteFile("root/textfile.txt"), 0);
		Assert::AreEqual(f1->getParent()->getName(), static_cast<string>("files"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == f1;
		Assert::IsTrue(same);
		// additional check that the file has NOT been removed from the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		same = ret == f1;
		Assert::IsTrue(same);
	}
	TEST_METHOD(deleteFileInvalidRoot) { // if we try to delete the root, we should recieve an error value returned
		HierarchicalFileSystem hfs;
		Assert::AreNotEqual(hfs.deleteFile("root"), 0);
	}
	TEST_METHOD(deleteFileInvalidOpenFile) { // if we try to delete an open file, we should recieve an error and the parent/child relationship should remain the same
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreEqual(hfs.addFile(filepath, f1), 0);
		AbstractFile* returnedFile = hfs.openFile(filepath);
		bool same = returnedFile == f1;
		Assert::IsTrue(same);
		Assert::AreNotEqual(hfs.deleteFile(filepath), 0);
		Assert::AreEqual(f1->getParent()->getName(), static_cast<string>("files"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		same = directoryChild == f1;
		Assert::IsTrue(same);
		// additional check that the file has NOT been removed from the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		same = ret == f1;
		Assert::IsTrue(same);
	}
	TEST_METHOD(addFileValid) { // check that parent and child relationship is properly set when adding valid files to the system
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreEqual(d1->getParent()->getName(), static_cast<string>("root"));
		Assert::AreEqual(f1->getParent()->getName(), static_cast<string>("files"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == f1;
		Assert::IsTrue(same);
		// additional check that the file has been added to the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		same = ret == f1;
		Assert::IsTrue(same);
	}
	TEST_METHOD(addNullFile) { // when adding a nullptr as a file we expect an error return value, and the directory file should not have a child
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = nullptr;
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreNotEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreEqual(d1->getParent()->getName(), static_cast<string>("root"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == nullptr;
		Assert::IsTrue(same);
		// additional check that the file has NOT been added to the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		bool isNull = ret == nullptr;
		Assert::IsTrue(isNull);
	}
	TEST_METHOD(addFileBadPath) { // check the case of a bad filepath, the new file should not be added as a child and we expect an error return value
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/newfiles/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreNotEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreEqual(d1->getParent()->getName(), static_cast<string>("root"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == nullptr;
		Assert::IsTrue(same);
		// additional check that the file has NOT been added to the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		bool isNull = ret == nullptr;
		Assert::IsTrue(isNull);
	}
	TEST_METHOD(addFileAlreadyExists) { // check the case of adding a file that already exists in a directory, the new file should not be added as a child again and we expect an error return value
		HierarchicalFileSystem hfs;
		AbstractFile* d1 = new DirectoryFile("files");
		AbstractFile* f1 = new TextFile("textfile.txt");
		string directorypath = "root/files";
		string filepath = "root/files/textfile.txt";
		Assert::AreEqual(hfs.addFile(directorypath, d1), 0);
		Assert::AreEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreNotEqual(hfs.addFile(filepath, f1), 0);
		Assert::AreEqual(d1->getParent()->getName(), static_cast<string>("root"));
		Assert::AreEqual(f1->getParent()->getName(), static_cast<string>("files"));
		AbstractFile* directoryChild = d1->getChild("textfile.txt");
		bool same = directoryChild == f1;
		Assert::IsTrue(same);
		// additional check that the file has been added once to the system using parsePath (parsePath checks must pass for this to work)
		AbstractFile* ret = hfs.parsePath(filepath);
		same = ret == f1;
		Assert::IsTrue(same);
	}
	};
}
