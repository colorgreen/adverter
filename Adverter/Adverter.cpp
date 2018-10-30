#include "pch.h"
#include <iostream>
#include "Database.h"
#include "MainMenu.h"
#include "Util.h"

using namespace std;

int main()
{
	Util::resetColor();

	Database::getContext();

	MainMenu menu;
	menu.run();
}
