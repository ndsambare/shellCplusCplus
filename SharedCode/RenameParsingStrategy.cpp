#include "AbstractCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"
#include "RenameParsingStrategy.h"
#include <string>
#include <vector>


using namespace std;

vector<string> RenameParsingStrategy::parse(string parseString) {
	vector<string> stringParser; 
	stringParser.push_back(parseString);
	string indexOne = parseString.substr(0, parseString.find_first_of(' ')); 
	stringParser.push_back(indexOne);

	return stringParser;
}