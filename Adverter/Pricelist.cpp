#include "pch.h"
#include "Pricelist.h"

REGISTER_STATICS(Pricelist)
int Pricelist::currentPricelist;

void Pricelist::setName(string name)
{
	this->name = name;
}

void Pricelist::setPrices(PERIODS prices)
{
	memcpy(this->prices, prices, _PERIODS * sizeof(double));
}


ostream& operator<<(ostream& output, const Pricelist& p)
{
	output << "Id cennika = " << p.id << "\nNazwa cennika = " << p.name << endl;
	for (int j = 0; j < 48; j++, output << endl)
	{
		cout.width(2);
		cout << j/2 << ":" << (j%2 ? "30" : "00") << "\t";
		for (int i = 0; i < 7; i++)
			cout << p.prices[i * 48 + j] << "\t";
	}

	return output;
}
