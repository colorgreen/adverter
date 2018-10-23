#pragma once
#include "DatabaseModel.h"
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class Pricelist : public DatabaseModel
{
public:
	TABLE(Pricelist)

	static int currentPricelist;

	static const int _PERIODS = 336;
	typedef double PERIODS[_PERIODS];
	enum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

	Pricelist();


	friend ostream& operator<<(ostream& output, const Pricelist& p);

	void setId(int id);
	void setName(string name);
	void setPrices(PERIODS prices);

	int getId() { return id; }
	auto getPrices() { return prices; }
	string getName() { return name; }
	double * getPricesForDay(int day) { return prices + day * 48; }

private:

	friend class Serializer;

	string name;
	PERIODS prices;
};

const int Pricelist::_PERIODS; // 7 * 24 * 2
