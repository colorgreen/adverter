#include "pch.h"
#include "Importer.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Pricelist.h"
#include "Database.h"
#include "Spot.h"
#include "Planner.h"


bool Importer::importPricelist(string name, string path)
{
	ifstream file(path);

	if (!file)
		return false;	

	Pricelist * pricelist = Database::getContext()->newObject<Pricelist>();

	pricelist->setName(name);

	string line;
	getline(file, line); // ignore first line (day names)

	for( int period=0; period<48; period++)
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
	}

	for (int i = 5; i <= 60; i+=5)
	{
		getline(file, line);
		replace(line.begin(), line.end(), ';', ' ');
		replace(line.begin(), line.end(), ',', '.');

		int duration;
		double factor;

		std::stringstream ss;
		ss << line;
		ss >> duration >> factor;

		pricelist->setFactorForDurration(duration, factor);
	}

	Database::getContext()->add(pricelist);

	if (Pricelist::table.size() == 1)
	{
		Pricelist::currentPricelist = pricelist->getId();
		Pricelist::current = pricelist;
	}
	Database::getContext()->save();

	return true;
}

bool Importer::importSpotsOptimal(string path)
{

	ifstream file(path);

	if (!file)
		return false;

	string line;
	getline(file, line); // ignore first line (day names)

	while (!file.eof())
	{
		if (line == "") break;

		getline(file, line);
		replace(line.begin(), line.end(), ' ', '/');
		replace(line.begin(), line.end(), ';', ' ');

		stringstream ss;
		string name, days, timeOfDays;
		int duration, spotsCount;

		ss << line;
		ss >> name >> duration >> days >> timeOfDays >> spotsCount;

		replace(name.begin(), name.end(), '/', ' ');

		Advertiser * advertiser = Database::getContext()->newObject<Advertiser>();
		advertiser->setName(name);

		Planner planner;
		planner.setType(Planner::OPTIMAL);
		planner.setAdvertiser(advertiser);
		planner.setDays(days);
		planner.setDuration(duration);
		planner.setTimeOfDays(timeOfDays);
		planner.setSpotsCount(spotsCount);

		planner.plan();
		planner.applySpots();

		Database::getContext()->add(advertiser);
	}

	Database::getContext()->save();
}