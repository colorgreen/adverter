#include "pch.h"
#include "Pricelist.h"

REGISTER_STATICS(Pricelist)
int Pricelist::currentPricelist;
Pricelist * Pricelist::current;

void Pricelist::setName(string name)
{
	this->name = name;
}

void Pricelist::setPrices(PERIODS prices)
{
	memcpy(this->prices, prices, _PERIODS * sizeof(double));
}


void Pricelist::setFactorForDurration(int duration, double factor)
{
	factors[duration] = factor;
}

ostream& operator<<(ostream& output, const Pricelist& p)
{
	output << "Id cennika = " << p.id << "\nNazwa cennika = " << p.name 
	<< endl << "Okres\tPON\tWT\tSR\tCZW\tPT\tSOB\tNDZ" << endl;
	for (int j = 0; j < 48; j++, output << endl)
	{
		cout.width(2);
		cout << j/2 << ":" << (j%2 ? "30" : "00") << "\t";
		for (int i = 0; i < 7; i++)
			cout << p.prices[i * 48 + j] << "\t";
	}

	output << endl << "MNOZNIKI: " << endl;
	for (int i = 5; i <= 60; i+=5)
		cout << i << "\" = " << p.factors.find(i)->second << endl;

	return output;
}


double Pricelist::getPrice(int duration, int day, int period)
{
	return this->getFactorForDuration(duration) * getPricesForDay(day)[period];
}
