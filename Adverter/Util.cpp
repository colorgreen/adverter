#include "pch.h"
#include "Util.h"


int Util::getPeriodFromTimeString(string period)
{
	if (period.size() != 5)
		throw new exception();
	int hh, mm;
	stringstream ss;
	ss << period.substr(0, 2) << " " << period.substr(3, 5);
	ss >> hh >> mm;
	return hh * 2 + mm / 30;
}

void Util::setConsoleColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Util::resetColor()
{
	setConsoleColor(DarkWhite);
}