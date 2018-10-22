#pragma once
#include "Menu.h"

class PricelistMenu : public Menu
{

	void import();
	void show();

public:
	PricelistMenu();
	~PricelistMenu();

	void handle(char c);
};

