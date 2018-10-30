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

Pricelist* PricelistMenu::choosePricelist()
{
	auto pricelists = Database::getContext()->get<Pricelist>();

	if( pricelists.size() == 0 )
	{
		cout << "Nie ma zadnych cennikow" << endl;
		return nullptr;
	}

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

	if (p == nullptr)
		return;

	function<bool(Pricelist*)> f = [](Pricelist* p) { return p->getId() == p->getId(); };
	auto pricelist = Database::getContext()->get<Pricelist>();

	cout << *p << endl;
	int day = Util::input<int>("Podaj dzien tyg ( 1 - pn, 2 - wt, 3 - sr, 4 - czw, 5 - pt, 6 - sob, 7 - ndz )");
	string period = Util::input<string>("Podaj godzine do edytowania");
	double price = Util::input<double>("Podaj nowa cene");

	int idx = Util::getPeriodFromTimeString(period);

	p->getPricesForDay(day - 1)[idx] = price;

	cout << "Zaktualizowano cennik pomyslnie" << endl;

	Database::getContext()->save();
}

void PricelistMenu::changeCurrent()
{
	auto p = choosePricelist();

	if (p == nullptr)
		return;

	Pricelist::currentPricelist = p->getId();
	Database::getContext()->save();

	Pricelist::current = Database::getContext()
	                     ->get<Pricelist>()
	                     .single(function<bool(Pricelist*)>([](Pricelist* p)
	                     {
		                     return p->getId() == Pricelist::currentPricelist;
	                     }));
}
