#pragma once
#include <vector>
#include <string>
#include <sstream>
#include "Spot.h"
#include "Advertiser.h"

using namespace std;

class Planner
{
	int type;
	int spotsCount;
	int duration;
	int daysCount;
	int budget;
	vector<int> days;
	vector<int> timeOfDays;
	DatabaseObjects<Spot*> spots;
	Advertiser * advertiser;

	void planOptimal();
	void planPriceTo();
public:
	enum { OPTIMAL = 1, PRICE_TO = 2 };

	void setAdvertiser(Advertiser * advertiser);
	void choosePlan();
	void plan();
	void getProposedSpots();
	void applySpots();


	void setDays(string);

	void setType(int type);
	void setTimeOfDays(string timeOfDays);
	void setSpotsCount(int spotsCount);
	void setDuration(int duration);
};
