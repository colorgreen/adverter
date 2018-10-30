#pragma once
#include "DatabaseModel.h"
#include <vector>
#include <string>

using namespace std;

class Spot : public DatabaseModel
{
	string name;
	double price;
	int id_advertiser;
	int period;
	int day;
	int duration;

	friend class Serializer;
public:
	TABLE(Spot)

	Spot();
	~Spot();

	void setName(string name);
	void setPrice(double price);
	void setAdvertiserId(int id);
	void setPeriod(int period);
	void setDay(int day);
	void setDuration(int duration);

	string getName() const { return name; }
	double getPrice() const { return price; }
	int getAdvertiserId() const { return id_advertiser; }
	int getPeriod() const { return period; }
	int getDay() const { return day; }
	int getDuration() const { return duration; }

	friend ostream & operator <<(ostream& output, const Spot& s);
};
