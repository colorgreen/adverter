#pragma once
#include "Menu.h"
#include <iostream>

using namespace std;

class AdvertiserMenu : public Menu
{

	void show();
	void import();

public:
	AdvertiserMenu();

	void handle(char c) override;
};

