#include "pch.h"
#include <iostream>
#include "Database.h"
#include "MainMenu.h"

using namespace std;

int main()
{
	Database::getContext();
//	Database::getContext()->reset();

	MainMenu menu;
	menu.run();
}
