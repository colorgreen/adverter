#include "pch.h"
#include "AdvertiserMenu.h"
#include  "Importer.h"
#include "Advertiser.h"

AdvertiserMenu::AdvertiserMenu()
{
	options =
		"1 - Pokaz reklamodawcow\n"
		"2 - Dodaj\n"
		"3 - Modyfikuj\n"
		"4 - Usun\n"
		"5 - Pokaz reklamodawce\n"
		"6 - Import\n"
		"q - Wroc\n";
}


void AdvertiserMenu::handle(char c)
{
	if (c == '1')
		show();
//	if (c == '2')
//		modify();
	if (c == '6')
		import();
//	if (c == '4')
//		changeCurrent();
}


void AdvertiserMenu::show()
{
	for (auto a : Advertiser::table)
		cout << *a << endl;
}


void AdvertiserMenu::import()
{
	string path, name;

	cin.ignore();
	cout << "Podaj sciezke do pliku cennika (.txt)" << endl;
	getline(cin, path);

	Importer importer;
	if (importer.importAdvertisers(path))
		cout << "Zaimportowano" << endl;
	else cout << "Nie zaimportowano!" << endl;
}
