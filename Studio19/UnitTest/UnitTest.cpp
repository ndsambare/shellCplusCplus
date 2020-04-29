#include "pch.h"
#include "CppUnitTest.h"

#define protected public
#include "../../SharedCode/TextFile.cpp"
#include "../../SharedCode/ImageFile.cpp"
#include "../../SharedCode/SimpleFileFactory.cpp"
#include "../../SharedCode/SimpleFileSystem.cpp"
#include "../../SharedCode/BasicDisplayVisitor.cpp"
#include "../../SharedCode/MetadataDisplayVisitor.cpp"
#include "../../SharedCode/PasswordProxy.cpp"
#include "../../SharedCode/TouchCommand.cpp"
#include "../../SharedCode/CommandPrompt.cpp"
#include "../../SharedCode/CommandTest.cpp"
#undef protected


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(textFile)
	{
	public:

		TEST_METHOD(contstructor)  // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.txt";
			unsigned int fileSize = 0;
			TextFile t(fileName);
			Assert::AreEqual(t.getName(), fileName);
			Assert::AreEqual(t.getSize(), fileSize);
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
			Assert::AreEqual(t.getSize(), static_cast<unsigned int>( v.size()));
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
	};
	TEST_CLASS(imageFile)
	{
	public:

		TEST_METHOD(contstructor) // checks that the file is initialized with proper name and size, expects size to be 0 and the name to match the input to the constructor
		{
			std::string fileName = "FileName.img";
			unsigned int fileSize = 0;
			ImageFile t(fileName);
			Assert::AreEqual(t.getName(), fileName);
			Assert::AreEqual(t.getSize(), fileSize);
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
		std::string fileName = "FileName.img";
		ImageFile t(fileName);
		std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
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
	TEST_CLASS(passwordProxy)
	{
	public:

		TEST_METHOD(contstructor) // we expect the name and size of the password proxy to match that of the text file it is assigned with
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			unsigned int fileSize = 0;
			// EXPECTATIONS FOR CONSTRUCTION
			Assert::AreEqual(pp->getName(), fileName);
			Assert::AreEqual(pp->getSize(), fileSize);
			Assert::AreEqual(realfile->getName(), fileName);
			Assert::AreEqual(realfile->getSize(), fileSize);
		}
		TEST_METHOD(writeValidPassword) // with a valid password, we would expect the size of the pasword proxy and realfile to be updated and return the same value (the size of the vector)
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			ss_in << password;
			// EXPECTATIONS FOR FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(writeInvalidPassword) // if an incorrect password is given, write should not execute and the size of both the password proxy and the real file should remain 0
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			string wrongPassword = "s9K3qL";
			ss_in << wrongPassword;
			// EXPECTATIONS FOR FUNCTION -- INVALID PASSWORD
			Assert::AreNotEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(0));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(0));
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(appendValidPassword) // we expect that if a good password is given for write and for append, then the proxy and real file should both only have their sizes updated accordingly 
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			unsigned int fileSize = pp->getSize();
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			Assert::AreEqual(pp->append(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(fileSize + v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(fileSize + v.size()));
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);

		}
		TEST_METHOD(appendInvalidPassword) //  we expect that if a good password is given for write, but an incorrect password is given for append, then the proxy and real file should both only have their sizes updated from the first write
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			unsigned int fileSize = pp->getSize();
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			Assert::AreNotEqual(pp->append(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(fileSize));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(fileSize));
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);

		}
		TEST_METHOD(readValidPassword) // we would expect to see the effects of writing to the proxy with a valid password in the content returned by the read function -- when a valid password is given -- this should also match the read content of the real file
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			// EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
			std::vector<char> contentsPP = pp->read();
			Assert::AreEqual(contentsPP.size(), v.size());
			for (size_t i = 0; i < contentsPP.size(); ++i) {
				Assert::AreEqual(v[i], contentsPP[i]);
			}
			std::vector<char> contentsRF = realfile->read();
			Assert::AreEqual(contentsRF.size(), v.size());
			for (size_t i = 0; i < contentsRF.size(); ++i) {
				Assert::AreEqual(v[i], contentsRF[i]);
			}
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(readInvalidPassword) // when an invalid password is given for the read function, then we would expect the contents vector returned to be empty, however the original file, that does not require a password to read, should be updated from the valid write call
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			std::vector<char> contentsPP = pp->read();
			Assert::AreEqual(static_cast<int>(contentsPP.size()), 0);
			std::vector<char> contentsRF = realfile->read();
			Assert::AreEqual(contentsRF.size(), v.size());
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(acceptValidPassword) // we would expect "hi" -- the contents of the file -- to be printed when a valid password is given for accept
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			ss_in << password + '\n' + password;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			// EXPECTATIONS FOR SECOND FUNCTION -- VALID PASSWORD
			BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
			pp->accept(bdv);
			string wordShouldBe = "hi";
			string word;
			vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
			bool isEqual = it1 == printedWords.end();
			Assert::IsFalse(isEqual);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(acceptInvalidPassword) // we do not expect "hi" (the contents of the file) to be printed when an invalid password is given for accept
		{
			// CREATE FILE AND FILE PROXY
			std::string fileName = "file1.txt";
			AbstractFile* realfile = new TextFile(fileName);
			string password = "r4A3dg";
			PasswordProxy* pp = new PasswordProxy(realfile, password);
			vector<char> v = { 'h', 'i' };
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
			// SET UP PASSWORD STREAM
			string wrongPassword = "a5lsdIK3";
			ss_in << password + '\n' + wrongPassword;
			// EXPECTATIONS FOR FIRST FUNCTION -- VALID PASSWORD
			Assert::AreEqual(pp->write(v), 0);
			Assert::AreEqual(pp->getSize(), static_cast<unsigned int>(v.size()));
			Assert::AreEqual(realfile->getSize(), static_cast<unsigned int>(v.size()));
			// EXPECTATIONS FOR SECOND FUNCTION -- INVALID PASSWORD
			BasicDisplayVisitor* bdv = new BasicDisplayVisitor;
			pp->accept(bdv);
			string wordShouldBe = "hi";
			string word;
			vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), wordShouldBe);
			bool isEqual = it1 == printedWords.end();
			Assert::IsTrue(isEqual);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
	};
	TEST_CLASS(commandPrompt) {
		TEST_METHOD(addAndListCommands) { // ensures the add command and list command are working correctly, we would expect the command name for the command we added (in this case the testCommand) to be printed out by the listCommand() method
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt cp;
			cp.setFileSystem(sfs);
			cp.setFileFactory(sff);
			// ADD COMMAND -- TEST COMMAND
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp.addCommand(commandname, ct), 0);
			// REDIRECT STD STREAM
			streambuf* backup;
			backup = cout.rdbuf();
			stringstream ss;
			cout.rdbuf(ss.rdbuf());
			// LIST COMMANDS
			cp.listCommands();
			string word;
			std::vector<string> printedWords;
			while (ss >> word) {
				printedWords.push_back(word);
			}
			// EXPECTATION -- COMMAND NAME SHOULD BE PRINTED TO COUT
			Assert::AreEqual(static_cast<int>(printedWords.size()), 1);
			Assert::AreEqual(printedWords[0], commandname);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup);
		}
		TEST_METHOD(prompt) { // checks prompt method, ensures that prompt returns what is typed in the terminal by the filesystem user
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
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
			// MIMIC USER INPUT -- SAMPLE COMMAND FOR TOUCH
			string input = "touch file.txt";
			ss_in << input;
			// EXPECTATION -- PROMPT SHOULD RETURN THE USER INPUT
			string promptResponse = cp->prompt();
			Assert::AreEqual(promptResponse, input);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(runQuit) { // ensures that the run method ends when quit by the user (entering q), we would expect a non-zero return value
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
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
			// MIMC USER INPUT -- QUITTING COMMAND -- 'Q'
			string input = "q";
			ss_in << input;
			// CAPUTRE RETURN VALUE -- Q SHOULD END THE RUN LOOP
			int response = cp->run();
			Assert::AreNotEqual(response, 0);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(runHelp) { // we would expect help to list all of the commands that have been added, in this case only the test command should be printed
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND -- COMMAND TEST
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
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
			// MIMIC USER INPUT -- HELP & QUIT -- USE QUIT TO END RUN 
			string input = "help\nq";
			ss_in << input;
			int response = cp->run();
			Assert::AreNotEqual(response, 0);
			// CAPTURE COUT DATA
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			// EXPECTATION -- PROGRAM SHOULD PRINT ALL COMMANDS
			std::vector<string>::iterator it1;
			it1 = std::find(printedWords.begin(), printedWords.end(), commandname);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
	};
	TEST_CLASS(commandTest) {
		TEST_METHOD(commandDisplayInfo) { // uses the CommandTest object to check that help + command name will successfully call the displayInfo() method for the correct command type
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
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
			// MIMIC USER INPUT -- SPECIFIC HELP COMMAND
			string input = "help test\nq\n";
			ss_in << input;
			int response = cp->run();
			Assert::AreNotEqual(response, 0);
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			/// EXPECTATION -- DISPLAY INFO OF OUR COMMAND TEST SHOULD BE PRINTED TO COUT
			std::vector<string>::iterator it1;
			string expectedString = "aRandomStringz"; // MATCHES GIVEN COMMAND TEST FILE
			it1 = std::find(printedWords.begin(), printedWords.end(), expectedString);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(commandExecuteNoInfo) { //  uses the CommandTest object to check passing variables to execute - expects no inputs to be passed as the parameter in this case
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
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
			// MIMIC USER INPUT -- COMMAND TEST EXECUTE 
			string input = "test\nq\n";
			ss_in << input;
			// CAPTURE RUN OUTPUT
			int response = cp->run();
			Assert::AreNotEqual(response, 0);
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			// EXPECTATION -- NOTHING SHOULD BE PASSED TO THE FUNCTION
			std::vector<string>::iterator it1;
			string expectedOutput = "command-test-no-info";
			it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(commandExecuteOneInput) { //  uses the CommandTest object to check passing variables to execute - expects one input, foo, to be passed to the function
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
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
			string input = "test foo\nq\n";
			ss_in << input;
			int response = cp->run();
			Assert::AreNotEqual(response, 0);
			string word;
			std::vector<string> printedWords;
			while (ss_out >> word) {
				printedWords.push_back(word);
			}
			// EXPECTATION -- THE SECOND PARAMETER SHOULD BE PRINTED TO COUT
			std::vector<string>::iterator it1;
			string expectedOutput = "foo";
			it1 = std::find(printedWords.begin(), printedWords.end(), expectedOutput);
			bool notEqual1 = it1 == printedWords.end();
			Assert::IsFalse(notEqual1);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
		TEST_METHOD(commandExecuteMoreInputs) { // uses the CommandTest object to check passing variables to execute - expects two inputs to be passed 
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			CommandTest* ct = new CommandTest(sfs);
			string commandname = "test";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
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
			Assert::AreNotEqual(response, 0);
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
			Assert::IsFalse(notEqual1);
			// ASSIGN COUT BACK TO STDOUT
			cout.rdbuf(backup_out);
			// ASSIGN CIN BACK TO STDIN
			cin.rdbuf(backup_in);
		}
	};
	TEST_CLASS(touchCommand) {
		TEST_METHOD(execute) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
			// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			TouchCommand* ct = new TouchCommand(sfs, sff);
			string commandname = "touch";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
			// CALL EXECUTE ON TOUCH COMMAND
			string filename = "file.txt";
			Assert::AreEqual(ct->execute(filename), 0);
			// EXPECTATION -- FILE EXISTS IN THE FILE SYSTEM
			AbstractFile* file = sfs->openFile(filename);
			bool isNull = file == nullptr;
			Assert::IsFalse(isNull);
			Assert::AreEqual(filename, file->getName());
		}
		TEST_METHOD(executeInvalidExtension) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
		// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			TouchCommand* ct = new TouchCommand(sfs, sff);
			string commandname = "touch";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
			// CALL EXECUTE ON TOUCH COMMAND
			string filename = "file.foo";
			Assert::AreNotEqual(ct->execute(filename), 0);
			// EXPECTATION -- FILE DOES NOT EXISTS IN THE FILE SYSTEM
			AbstractFile* file = sfs->openFile(filename);
			bool isNull = file == nullptr;
			Assert::IsTrue(isNull);
		}
		TEST_METHOD(executeFileAlreadyExists) { // confirms that execute, when passed a valid filename, will create and add a file in the filesystem
		// SET UP FILE SYSTEM
			AbstractFileSystem* sfs = new SimpleFileSystem();
			AbstractFileFactory* sff = new SimpleFileFactory();
			CommandPrompt* cp = new CommandPrompt;
			cp->setFileSystem(sfs);
			cp->setFileFactory(sff);
			// ADD COMMAND
			TouchCommand* ct = new TouchCommand(sfs, sff);
			string commandname = "touch";
			Assert::AreEqual(cp->addCommand(commandname, ct), 0);
			// CALL EXECUTE ON TOUCH COMMAND
			string filename = "file.txt";
			Assert::AreEqual(ct->execute(filename), 0);
			Assert::AreNotEqual(ct->execute(filename), 0);
			// EXPECTATION -- FILE DOES EXISTS IN THE FILE SYSTEM - FIRST EXECUTION
			AbstractFile* file = sfs->openFile(filename);
			bool isNull = file == nullptr;
			Assert::IsFalse(isNull);
		}
	};
	
}
