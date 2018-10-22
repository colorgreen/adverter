#include "pch.h"
#include "Pricelist.h"
#include <iostream>

REGISTER_STATICS(Pricelist)

Pricelist::Pricelist()
{
}

void Pricelist::setName(string name)
{
	this->name = name;
}

void Pricelist::setId(int id)
{
	this->id = id;
}

void Pricelist::setPrices(PERIODS prices)
{
	memcpy(this->prices, prices, _PERIODS * sizeof(double));
}


ostream& operator<<(ostream& output, const Pricelist& p)
{
	output << "Id cennika = " << p.id << "\nNazwa cennika = " << p.name << endl;
	for (int j = 0; j < 48; j++, output << endl)
		for (int i = 0; i < 7; i++)
			cout << p.prices[i*48+j] << "\t";
	
	return output;
}
