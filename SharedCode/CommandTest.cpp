#include "CommandTest.h"
using namespace std;

CommandTest::CommandTest(AbstractFileSystem* _afs, AbstractFileFactory* _aff): afs(_afs), aff(_aff)
{
}

int CommandTest::execute(std::string first, std::string second)
{
	std::replace(second.begin(), second.end(), ' ', ':');
	cout << "\n" << first << ":" << second << "\n" << endl;
	return success;
}

void CommandTest::displayInfo()
{
	cout << "aRandomStringz" << endl;
}
