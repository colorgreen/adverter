#include "pch.h"
#include "PricelistImporter.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Pricelist.h"
#include "Database.h"


bool PricelistImporter::import(string name, string path)
{
	ifstream file(path);

	if (!file)
		return false;	

	Pricelist * pricelist = Database::getContext()->newObject<Pricelist>();

	pricelist->setName(name);

	string line;
	getline(file, line); // ignore first line (day names)

	int period = 0;
	while (!file.eof())
	{
		getline(file, line);
		replace(line.begin(), line.end(), ';', ' ');

		string p;
		double d0, d1, d2, d3, d4, d5, d6;

		std::stringstream ss;
		ss << line;
		ss >> p >> d0 >> d1 >> d2 >> d3 >> d4 >> d5 >> d6;

		pricelist->getPricesForDay(0)[period] = d0;
		pricelist->getPricesForDay(1)[period] = d1;
		pricelist->getPricesForDay(2)[period] = d2;
		pricelist->getPricesForDay(3)[period] = d3;
		pricelist->getPricesForDay(4)[period] = d4;
		pricelist->getPricesForDay(5)[period] = d5;
		pricelist->getPricesForDay(6)[period] = d6;

		period++;
	}

	Database::getContext()->add(pricelist);

	if (Pricelist::table.size() == 1)
		Pricelist::currentPricelist = pricelist->getId();

	Database::getContext()->save();

	return true;
}


