#include "pch.h"
#include "PricelistMenu.h"
#include <iostream>
#include <vector>
#include <sstream>
#include "Importer.h"
#include "Database.h"
#include "Util.h"

using namespace std;

PricelistMenu::PricelistMenu()
{
	options =
		"1 - Pokaz cennik\n"
		"2 - Edytuj cennik\n"
		"3 - Importuj cennik\n"
		"4 - Zmien aktualny cennik\n"
		"q - Wroc\n";
}

void PricelistMenu::handle(char c)
{
	if (c == '1')
		show();
	if (c == '2')
		modify();
	if (c == '3')
		import();
	if (c == '4')
		changeCurrent();
}

void PricelistMenu::import()
{
	string path, name;

	cin.ignore();
	cout << "Podaj nazwe cennika" << endl;
	getline(cin, name);
	cout << "Podaj sciezke do pliku cennika (.csv)" << endl;
	getline(cin, path);

	Importer importer;
	if (importer.importPricelist(name, path))
		cout << "Zaimportowano " << name << endl;
	else cout << "Nie zaimportowano cennika!" << endl;
}

void PricelistMenu::show()
{
	cout << "Aktualny cennik id: " << Pricelist::currentPricelist << endl;
	for (Pricelist* p : Pricelist::table)
		cout << *p << endl;
	cout << endl;
}

Pricelist * PricelistMenu::choosePricelist()
{
	auto pricelists = Database::getContext()->all<Pricelist>();

	cout << "Cenniki do wyboru" << endl;
	int in, i = 1;
	for (auto p : pricelists)
		cout << i++ << " - " << p->getName() << endl;

	cout << "\nWybierz cennik (nr z listy)" << endl;
	cin >> in;

	if (in <= i)
	{
		return pricelists[in - 1];
	}
	cout << "Nie ma takiego cennika" << endl;
	return nullptr;
}


void PricelistMenu::modify()
{
	auto p = choosePricelist();

	function<bool(Pricelist*)> f = [](Pricelist* p) { return p->getId() == p->getId(); };
	auto pricelist = Database::getContext()->all<Pricelist>();

	cout << *p << endl;
	int day = Util::input<int>("Podaj dzien tyg (1 - poniedzialek, ..., 7 - niedziela");
	string time = Util::input<string>("Podaj godzine do edytowania");
	double price = Util::input<double>("Podaj nowa cene");

	int idx = getIndexFromPeriod(time);

	p->getPricesForDay(day-1)[idx] = price;

	cout << "Zaktualizowano cennik pomyslnie" << endl;

	Database::getContext()->save();
}

void PricelistMenu::changeCurrent()
{
	auto p = choosePricelist();

	Pricelist::currentPricelist = p->getId();
	Database::getContext()->save();
}

int PricelistMenu::getIndexFromPeriod(string period)
{
	int hh, mm;
	stringstream ss;
	ss << period.substr(0, 2) << " " << period.substr(3, 5);
	ss >> hh >> mm;
	return hh * 2 + mm / 30;
}
