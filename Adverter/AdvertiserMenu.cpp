#include "pch.h"
#include "AdvertiserMenu.h"
#include  "Importer.h"
#include "Advertiser.h"
#include "Planner.h"
#include "Util.h"

AdvertiserMenu::AdvertiserMenu()
{
	options =
		"1 - Pokaz reklamodawcow\n"
		"2 - Dodaj\n"
		"3 - Usun\n"
		"4 - Pokaz reklamodawce\n"
		"q - Wroc\n";
}


void AdvertiserMenu::handle(char c)
{
	if (c == '1')
		show();
	if (c == '2')
		add();
	if (c == '3')
		remove();
	if (c == '4')
		showDetails();
}


void AdvertiserMenu::show()
{
	for (auto a : Advertiser::table)
		cout << *a << endl;
}


void AdvertiserMenu::showDetails()
{
	const auto db = Database::getContext();

	auto advertiser = chooseAdvertiser();

	int sumPrice = db->get<Spot>()
	                 .where(function<bool(Spot*)>(
		                 [advertiser](Spot* spot)
		                 {
			                 return spot->getAdvertiserId() == advertiser->getId();
		                 }))
	                 .sum(function<double(Spot*)>([](Spot* spot) { return spot->getPrice(); }));

						 cout << "Calkowity koszt spotow: " << sumPrice << endl << endl;

	cout << "Okres\tPON\t\tWT\t\tSR\t\tCZW\t\tPT\t\tSOB\t\tNDZ" << endl;

	for (int period = 0; period < 48; period++, cout << endl)
	{
		cout.width(2);
		cout << period / 2 << ":" << (period % 2 ? "30" : "00") << "\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period, advertiser](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period && spot->getAdvertiserId() == advertiser->getId();
			};
			int count = db->get<Spot>().count(condition);

			if (count > 0)
			{
				Util::setConsoleColor(Util::LightAqua);
				cout << count << " spotow\t";
				Util::resetColor();
			}
			else
				cout << count << " spotow\t";
		}

		cout << "\n\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period, advertiser](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period && spot->getAdvertiserId() == advertiser->getId();
			};
			cout << db->get<Spot>().where(condition).sum(function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); })) <<
				"\" czas  \t";
		}
	}
}

void AdvertiserMenu::add()
{
	string name;
	cin.ignore();
	cout << "Podaj nazwe reklamodawcy" << endl;
	getline(cin, name);

	auto advertiser = Database::getContext()->newObject<Advertiser>();
	advertiser->setName(name);

	Planner planner;
	planner.setAdvertiser(advertiser);
	planner.choosePlan();
	planner.plan();
	planner.getProposedSpots();


	char confirm = Util::input<char>("Czy zatwierdzasz ustawienie? 1 - Tak, q - Nie");

	if (confirm == '1')
	{
		planner.applySpots();

		Database::getContext()->add(advertiser);
		Database::getContext()->save();

		cout << "Zapisano!" << endl;
	}
	else
		cout << "Przerwano operacje" << endl;
}

void AdvertiserMenu::remove()
{
	auto advertiser = chooseAdvertiser();
	if (advertiser == nullptr)
		return;

	function<bool(Spot*)> condition = [advertiser](Spot* spot) { return spot->getAdvertiserId() == advertiser->getId(); };
	auto spots = Database().getContext()->get<Spot>().where(condition);

	for (Spot* spot : spots)
		Database::getContext()->remove(spot);

	Database::getContext()->remove(advertiser);
	Database::getContext()->save();
}

Advertiser* AdvertiserMenu::chooseAdvertiser()
{
	auto advertisers = Database::getContext()->get<Advertiser>();

	if (advertisers.size() == 0)
	{
		cout << "Nie ma zadnych reklamodawcow" << endl;
		return nullptr;
	}

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
