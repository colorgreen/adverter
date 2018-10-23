#include "pch.h"
#include "Advertiser.h"

REGISTER_STATICS(Advertiser)

void Advertiser::setName(string name)
{
	this->name = name;
}

ostream& operator<<(ostream& output, const Advertiser& p)
{
	output << "Id reklamodawcy = " << p.id << "\nNazwa reklamodawcy = " << p.name << endl;
	return output;
}


