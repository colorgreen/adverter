#include "pch.h"
#include <iostream>
#include "Database.h"
#include "MainMenu.h"
#include "Util.h"

using namespace std;

int main()
{
	Util::resetColor();

	MainMenu menu;
	menu.run();
}
