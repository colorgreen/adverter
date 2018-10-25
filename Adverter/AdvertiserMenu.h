#pragma once
#include "Menu.h"
#include <iostream>
#include "Database.h"

using namespace std;

class AdvertiserMenu : public Menu
{
	void add();
	void modify();
	void remove();
	void show();
	void import();

	Advertiser * chooseAdvertiser();

public:
	AdvertiserMenu();

	void handle(char c) override;
};

