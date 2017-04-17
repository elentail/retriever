#include "Poco/Glob.h"
#include "Poco/StringTokenizer.h"
#include "Poco/String.h" // for cat

#include <iostream>
#include <string>

using namespace std;
using Poco::Glob;
using Poco::StringTokenizer;

int main(int argc, char** argv)
{
	std::set<std::string> files;
	

	string raw("C:\\Users\\roadking\\Downloads\\[]*.exe");
	StringTokenizer tokens(raw,R"_(\)_",StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
	for (const auto& str : tokens) {
		cout << str << endl;
	}


	Glob::glob(raw, files);

	cout << raw << endl;
	// Glob::glob("/usr/include/*/*.h", files);

	std::set<std::string>::iterator it = files.begin();

	for (; it != files.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}