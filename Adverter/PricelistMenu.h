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

	int getIndexFromPeriod(string period);
public:
	PricelistMenu();
	~PricelistMenu();

	void handle(char c);
};

