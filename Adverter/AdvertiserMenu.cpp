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
	if (c == '2')
		add();
	if (c == '3')
		modify();
	if (c == '4')
		remove();
	if (c == '5')
		show();
	if (c == '6')
		import();

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

void AdvertiserMenu::add() {

	string name;
	cin.ignore();
	cout << "Podaj nazwe reklamodawcy" << endl;
	getline(cin, name);

	auto advertiser = Database::getContext()->newObject<Advertiser>();
	advertiser->setName(name);

	Database::getContext()->add(advertiser);
	Database::getContext()->save();

	cout << "Zapisano!" << endl;
}

void AdvertiserMenu::modify() {
	auto advertiser = chooseAdvertiser();

}

void AdvertiserMenu::remove()
{
	auto advertiser = chooseAdvertiser();
	Database::getContext()->remove(advertiser);
	Database::getContext()->save();
}

Advertiser * AdvertiserMenu::chooseAdvertiser()
{
	auto advertisers = Database::getContext()->all<Advertiser>();

	cout << "Reklamodawcy do wyboru" << endl;
	int in, i = 1;
	for (auto p : advertisers)
		cout << i++ << " - " << p->getName() << endl;

	cout << "\nWybierz reklamodawce (nr z listy)" << endl;
	cin >> in;

	if (in <= i)
	{
		return advertisers[in - 1];
	}
	cout << "Nie ma takiego reklamodawcy" << endl;
	return nullptr;
}