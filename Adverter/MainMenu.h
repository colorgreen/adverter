#pragma once
#include "Menu.h"

class MainMenu : public Menu
{

public:
	MainMenu();
	
	void handle(char c);
};
