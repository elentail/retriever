#pragma once
#include "common.h"
#include "base_data.h"

class Parser
{

public:
	Parser() {}
	~Parser() {}
	void set_parse(Base_data& t) {
		engine[t.get_name()] = bind(&Base_data::parse, &t, placeholders::_1, placeholders::_2);
	}

	void do_parser(string test1,string test2)
	{
		engine["base"](test1, test2);
	}

private:
	
	map < string, function<bool(string,string)>> engine;
};