studio 19 answers here

2. Below is the code for our main function:
	AbstractFileFactory* aff = new SimpleFileFactory;
	AbstractFile* test = aff->createFile("test.txt");
	vector<char> addedContent{ 'n','i','c','e' };
	test->write(addedContent);
	vector<char> savedContents = test->read();
	vector<char> newAddedContent{ 'c','o','o','l' };
	test->write(newAddedContent);
	for (char c : savedContents) {
		cout << c << endl;
	}
	for (char c : test->read()) {
		cout << c << endl;
	}
It successfully saved the input elements into a vector during the write phase and outputted that vector during the read phase. Then, it was overwritten with new characters and then returned that in a vector.

3. The abstract file visitor can visit the concrete classes via the accept method called on those concrete types.

4. Delegation is helpful because it reduces clutter for the main class. It can extract the necessary information from it by simply peering into its data.

5. To add a new concrete class, many different files would have to be edited. We would need an accept method in the concrete class, and new visit methods in the AbstractFileVisitor, BasicDisplayVisitor, and MetadataDisplayVisitor. If the data you want is relatively straightforward, it might be worth it to build it into the concrete class rather than having a visitor because adding new concrete classes adds on extra methods for every visitor class.