#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

class Util
{
public:
	
	enum Color { DarkBlue = 1, DarkGreen, DarkAqua, DarkRed, DarkWhite=7, LightGreen = 10, LightAqua, LightRed, LightWhite = 15 };

	template<typename T>
	static T input( string message )
	{
		T t;
		cout << message << ": ";
		cin >> t;
		cout << endl;
		return t;
	}

	static int getPeriodFromTimeString(string period);

	static void setConsoleColor(int color);

	static void resetColor();
};

