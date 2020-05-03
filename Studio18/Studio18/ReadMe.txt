studio 18 answers here
1. Namit Sambare and William Loh
2. The factory method allows the derived classes of a base class to alter the type it creates in a method - i.e. polymorphic creation. The type of file system described in the question seems easy to implement if we follow the factory method. The base class AbstractFileSystem will create a general template for the createFile method, while the derived classes will specify the type for the concrete type needed.
3. Disadvantages of abstract factory is if you don't need subclasses, then you shouldn't use it. You would want to create a new concrete file class if there is a new type you are dealing with. To accommodate different file types, you would have to edit the createFile code to properly create that file type. Yes, the same factory can be used for both. Yes, it can be used for both (less sure).
4. This is the test we ran:
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
The result was the output: "nicenice"
5. Now it only depends on the AbstractFile interface.