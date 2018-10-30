#pragma once
#include <fstream>
#include "DatabaseObjects.h"

#define TABLE(type) \
	static int newId; \
	static DatabaseObjects<type*> table;

#define REGISTER_STATICS(type) \
	int type::newId; \
	DatabaseObjects<type*> type::table;



class DatabaseModel
{
protected:

	int id;

public:

	void setId(int id);

	auto getId() const { return id; }
};
