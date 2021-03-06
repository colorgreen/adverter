#pragma once
#include "Menu.h"
#include "Pricelist.h"

using namespace std;

class PricelistMenu : public Menu
{

	void import();
	void modify();
	void changeCurrent();
	void show();

	Pricelist * choosePricelist();

	public:
	PricelistMenu();

	void handle(char c) override;
};

