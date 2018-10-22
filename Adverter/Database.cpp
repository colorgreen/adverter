#include "pch.h"
#include "Database.h"
#include <fstream>
#include "Advertiser.h"

using namespace std;

Database* Database::instance = nullptr;

bool Database::load() const
{
	Serializer file(filename);

	if (!file)
		return false;

	file.read(Pricelist::newId);
	file.read(Advertiser::newId);
	cout << file.tellg() << endl;

	loadTable<Pricelist>(file);

	file.close();
	return true;
}

bool Database::save() const
{
	Serializer file(filename);

	if (!file)
		return false;

	file.write(Pricelist::newId);
	file.write(Advertiser::newId);
	cout << file.tellg() << endl;

	saveTable<Pricelist>(file);

	file.close();
	return true;
}

void Database::reset() const
{
	Pricelist::newId = 0;
	Advertiser::newId = 0;

	save();
}


Database* Database::getContext()
{
	if (instance)
		return instance;

	instance = new Database();
	if (!instance->load())
		if (!instance->save())
			throw exception("could not create database file");
	return instance;
}
