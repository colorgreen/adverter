#include "pch.h"
#include "Planner.h"
#include "Util.h"
#include <iterator>
#include <algorithm>
#include "Database.h"


void Planner::choosePlan()
{
	type = Util::input<int>(
		"Wybierz plan:\n"
		"1 - OPTYMALNY (podajesz dni, pore dnia, dlugosc spotow, ilosc spotow)\n"
		"2 - PROG CENY (podajesz dni, pore dnia, dlugosc spotow, twoj budzet)");

	string days = Util::input<string>(
		"Podaj dni 1 (pn) - 7 (ndz), oddzielajac przecinkami (np. \'6,7\' - spoty beda w sobote i niedziele");
	string timeOfDays = Util::input<string>(
		"Podaj pory dnia, oddzielajac przecinkami (np. \'2,3\' - spoty beda od 06:00 do 18:00"
		"\n1 - 00:00 - 06:00\n2 - 06:00 - 12:00\n3 - 12:00 - 18:00\n4 - 18:00 - 24:00");
	duration = Util::input<int>("Podaj dlugosc spotow w sekundach ( 5 - 5 sekund)");
	if (type == OPTIMAL)
	{
		spotsCount = Util::input<int>("Podaj ilosc spotow");
	}
	else if (type == PRICE_TO)
	{
		budget = Util::input<int>("Podaj budzet na reklamy");
	}

	setDays(days);
	setTimeOfDays(timeOfDays);
}


void Planner::planOptimal()
{
	int leftSpots = spotsCount;
	int prevSpotsLeftCount = 0;

	const auto db = Database::getContext();

	while (leftSpots >= 0)
	{
		if (prevSpotsLeftCount == leftSpots)
		{
			cout << "\n\t\tNIE MO¯NA PRZYDZIELIC WSZYSTKICH SPOTOW, PONIEWAZ PLAN JEST ZBYT ZAJETY\n" << endl;
			break;
		}

		prevSpotsLeftCount = leftSpots;

		for (auto day : days)
		{
			for (auto timeOfDay : timeOfDays)
			{
				int startPeriod = timeOfDay * 12; // 6 hours * 2 periods per our
				int endPeriod = (timeOfDay+1) * 12;

				for (int period = startPeriod; period < endPeriod && leftSpots >= 0; period++)
				{
					double time = db->get<Spot>().where(
						function<bool(Spot*)>([day, period](Spot* spot)
						{
							return spot->getDay() == day && spot->getPeriod() == period;
						})
					).sum(
						function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); })
					);

					if (time + duration <= 600 )
					{
						Spot* spot = Database::getContext()->newObject<Spot>();
						spot->setDuration(duration);
						spot->setPeriod(period);
						spot->setDay(day);
						spot->setPrice(Pricelist::current->getPrice(duration, day, period));
						spot->setAdvertiserId(advertiser->getId());
						spot->setName("reklama " + advertiser->getName());
						spots.push_back(spot);

						leftSpots--;
					}
				}
			}
		}
	}
}

void Planner::planPriceTo()
{
	int budget = this->budget;
	bool budgetEnded = false;

	const auto db = Database::getContext();

	while( budget > 0 )
	{
		for (auto day : days)
		{
			for (auto timeOfDay : timeOfDays)
			{
				int startPeriod = timeOfDay * 12; // 6 hours * 2 periods per our
				int endPeriod = (timeOfDay + 1) * 12;

				for (int period = startPeriod; period < endPeriod && !budgetEnded; period++)
				{
					double time = db->get<Spot>().where(
						function<bool(Spot*)>([day, period](Spot* spot)
					{
						return spot->getDay() == day && spot->getPeriod() == period;
					})
						).sum(
							function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); })
						);

					if(budget - Pricelist::current->getPrice(duration, day, period) < 0)
						return;

					if (time + duration <= 600 && budget - Pricelist::current->getPrice(duration, day, period) > 0)
					{
						Spot* spot = Database::getContext()->newObject<Spot>();
						spot->setDuration(duration);
						spot->setPeriod(period);
						spot->setDay(day);
						spot->setPrice(Pricelist::current->getPrice(duration, day, period));
						spot->setAdvertiserId(advertiser->getId());
						spot->setName("reklama " + advertiser->getName());
						spots.push_back(spot);

						budget -= spot->getPrice();
					}
				}
			}
		}
	}
}

void Planner::plan()
{
	for (auto spot : spots)
		delete spot;
	spots.clear();

	if (type == OPTIMAL)
		planOptimal();
	else if (type == PRICE_TO)
		planPriceTo();
}

void Planner::setDays(string days)
{
	replace(days.begin(), days.end(), ',', ' ');
	istringstream iss(days);
	this->days = vector<int>((istream_iterator<int>(iss)),
	                         istream_iterator<int>());
	daysCount = this->days.size();

	for (int i = 0; i < daysCount; i++)
		this->days[i] -= 1;
}

void Planner::setTimeOfDays(std::string timeOfDays)
{
	replace(timeOfDays.begin(), timeOfDays.end(), ',', ' ');
	istringstream iss(timeOfDays);
	this->timeOfDays = vector<int>((istream_iterator<int>(iss)),
	                               istream_iterator<int>());

	for (int i = 0; i < this->timeOfDays.size(); i++)
		this->timeOfDays[i] -= 1;
}

void Planner::setAdvertiser(Advertiser* advertiser)
{
	this->advertiser = advertiser;
}


void Planner::getProposedSpots()
{
	cout << "Proponowane spoty" << endl;
	int i = 0;
	for (Spot* spot : spots)
		cout << ++i << ". " << *spot << endl;

	const auto db = Database::getContext();

	double sumPrice = spots.sum(function<double(Spot*)>([](Spot*spot) { return spot->getPrice(); }));
	cout << "Calkowity koszt spotow: " << sumPrice << endl << endl;

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
			cout << db->get<Spot>().count(condition) << " spotow\t";
		}

		cout << "\n\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period;
			};
			cout << db->get<Spot>().where(condition).sum(function<int(Spot*)>([](Spot* spot) { return spot->getDuration(); })) <<
				"\" czas  \t";
		}

		cout << "\n\t";
		for (int day = 0; day < 7; day++)
		{
			function<bool(Spot*)> condition = [day, period](Spot* spot)
			{
				return spot->getDay() == day && spot->getPeriod() == period;
			};
			int count = spots.count(condition);
			if (count > 0)
			{
				Util::setConsoleColor(Util::LightGreen);
				cout << "+" << count << " spotow\t";
				Util::resetColor();
			}
			else cout << "\t\t";
		}
	}
}

void Planner::applySpots()
{
	for (Spot* spot : spots)
		Database::getContext()->add(spot);
	Database::getContext()->save();
}

void Planner::setType(int type)
{
	this->type = type;
}

void Planner::setSpotsCount(int spotsCount)
{
	this->spotsCount = spotsCount;
}

void Planner::setDuration(int duration)
{
	this->duration = duration;
}
