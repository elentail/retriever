#pragma once
#include "common.h"

class Base_data
{
public:
	Base_data() {};
	~Base_data() {};

	string get_name() {
		return "base";
	}

	bool parse(const string& param1, const string& param2)
	{
		ifstream ifs;
		ofstream ofs;
		ifs.open(param1, ios::in | ios::binary);
		ofs.open(param2, ios::out | ios::binary);

		ofs << ifs.rdbuf();

		ofs.close();
		ifs.close();
		return true;
	}
};