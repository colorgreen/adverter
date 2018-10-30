#include "pch.h"
#include "Spot.h"
#include <iostream>


REGISTER_STATICS(Spot)


Spot::Spot()
{
}


Spot::~Spot()
{
}

void Spot::setAdvertiserId(int id)
{
	id_advertiser = id;
}

void Spot::setName(string name)
{
	this->name = name;
}

void Spot::setPrice(double price)
{
	this->price = price;
}

void Spot::setDay(int day)
{
	this->day = day;
}

void Spot::setPeriod(int period)
{
	this->period = period;
}

void Spot::setDuration(int duration)
{
	this->duration = duration;
}

ostream& operator<<(ostream& output, const Spot& s)
{
	string DAYS[] = { "PN", "WT", "SR", "CZW", "PT", "SOB", "NDZ" };
	output.width(2);
	output << DAYS[s.day] << "\t" << s.period/2 << ":" << (s.period % 2 ? "30" : "00")
	<<"\tdl:" << s.duration << "s\tcena: " << s.price << "\tnazwa:" << s.name;
	return output;
}
