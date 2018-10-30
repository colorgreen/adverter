#pragma once
#include "DatabaseModel.h"
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Pricelist : public DatabaseModel
{
public:
	TABLE(Pricelist)

	static int currentPricelist;
	static Pricelist * current;

	static const int _PERIODS = 336;
	typedef double PERIODS[_PERIODS];
	enum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	
	friend ostream& operator<<(ostream& output, const Pricelist& p);

	void setName(string name);
	void setPrices(PERIODS prices);
	void setFactorForDurration(int duration, double factor);

	auto getPrices() const { return prices; }
	auto getName() const { return name; }
	double * getPricesForDay(int day) { return prices + day * 48; }
	double getFactorForDuration(int duration) const { return factors.find(duration/5*5)->second; };

	double getPrice(int duration, int day, int time);
private:

	friend class Serializer;

	string name;
	PERIODS prices;

	map<int, double> factors;
};

const int Pricelist::_PERIODS; // 7 * 24 * 2
