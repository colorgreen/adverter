#pragma once
#include <fstream>
#define TABLE(type) \
	static int newId; \
	static vector<type*> table;

#define REGISTER_STATICS(type) \
	int type::newId; \
	std::vector<type*> type::table;



class DatabaseModel
{
protected:
	int id;

public:

	void setId(int id)
	{
		this->id = id;
	}
};
