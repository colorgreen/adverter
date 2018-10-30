#include "pch.h"
#include "AdvertsMenu.h"
#include "Spot.h"
#include "Importer.h"
#include "Database.h"
#include "Util.h"


AdvertsMenu::AdvertsMenu()
{
	options =
		"1 - Pokaz wszystkie\n"
		"2 - Pokaz zajetosc\n"
		"3 - Pokaz w obszarze\n"
		"4 - Importuj\n"
		"q - Wroc\n";
}


void AdvertsMenu::show()
{
	for (Spot* s : Database::getContext()->get<Spot>())
		cout << *s << endl;
}

void AdvertsMenu::showTimetable()
{
	const auto db = Database::getContext();

	cout << "Okres\tPON\t\tWT\t\tSR\t\tCZW\t\tPT\t\tSOB\t\tNDZ" << endl;

	for (int period = 0; period < 48; period++, cout << endl)
	{
		cout.width(2);
		cout << period / 2 << ":" << (period % 2 ? "30" : "00") << "\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period;
			};
			int count = db->get<Spot>().count(condition);
			if (count > 0)
				cout << count << " spotow\t";
			else cout << "\t\t";
		}

		cout << "\n\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period;
			};
			int sum = db->get<Spot>().where(condition).sum(function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); }));
			if (sum > 0)
				cout << sum << "\" czas  \t";
			else cout << "\t\t";
		}
	}
}


void AdvertsMenu::showPeriod()
{
	int day = Util::input<int>("Podaj dzien tyg ( 1 - pn, 2 - wt, 3 - sr, 4 - czw, 5 - pt, 6 - sob, 7 - ndz )") - 1;
	int period = Util::getPeriodFromTimeString(Util::input<string>("Podaj godzine do edytowania ( format hh:mm )"));

	auto spots = Database::getContext()
	             ->get<Spot>()
	             .where(
		             function<bool(Spot*)>(
			             [day, period](Spot* spot)
			             {
				             return spot->getDay() == day && spot->getPeriod() == period;
			             }
		             )
	             );

	for (Spot* s : spots)
		cout << *s << endl;
	cout << "Razem  " << spots.count() << " spoty"
		<< " dl: " << spots.sum(function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); }))
		<< "\" cena dl: " << spots.sum(function<int(Spot*)>([](Spot* spot) { return spot->getPrice(); })) << endl << endl;
}

void AdvertsMenu::import()
{
	string path, name;

	cin.ignore();
	cout << "Podaj sciezke do pliku z reklamodawcami (.csv)" << endl;
	getline(cin, path);

	Importer importer;
	if (importer.importSpotsOptimal(path))
		cout << "Zaimportowano" << endl;
	else cout << "Nie zaimportowano!" << endl;
}

void AdvertsMenu::handle(char c)
{
	if (c == '1')
		show();
	if (c == '2')
		showTimetable();
	if (c == '3')
		showPeriod();
	if (c == '4')
		import();
}
