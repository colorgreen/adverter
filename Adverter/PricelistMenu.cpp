#include "pch.h"
#include "PricelistMenu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include "PricelistImporter.h"
#include "Pricelist.h"

using namespace std;

PricelistMenu::PricelistMenu()
{
	options =
		"1 - Pokaz cennik\n"
		"2 - Edytuj cennik\n"
		"3 - Importuj cennik\n"
		"q - Wyjscie\n";
}

void PricelistMenu::handle(char c)
{
	if (c == '1')
		show();
	if (c == '3')
		import();
}

void PricelistMenu::import()
{
	string path;

	cout << "Podaj sciezke do pliku cennika (.csv)" << endl;
	cin >> path;

	PricelistImporter importer;
	if (!importer.import( "Cennik 1", path))
		cout << "Nie zaimportowano cennika!" << endl;

}

void PricelistMenu::show()
{
	for (auto p : Pricelist::table)
		cout << *p << endl;
}
