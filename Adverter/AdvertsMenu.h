#pragma once
#include "Menu.h"
#include <iostream>

using namespace std;

class AdvertsMenu : public Menu
{
	void show();
	void showTimetable();
	void showPeriod();
	void import();


public:
	AdvertsMenu();

	void handle(char c) override;
};

