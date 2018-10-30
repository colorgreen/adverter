#include "pch.h"
#include "MainMenu.h"
#include "PricelistMenu.h"
#include "AdvertiserMenu.h"
#include <iostream>
#include "AdvertsMenu.h"

using namespace std;

MainMenu::MainMenu()
{
	options =
		"1 - Cennik\n"
		"2 - Reklamodawcy\n"
		"3 - Reklamy\n"
		"q - Wyjscie\n";
}


void MainMenu::handle(char c)
{
	Menu * menu = nullptr;
	
	if( c == '1' )
		menu = new PricelistMenu();
	if( c =='2' )
		menu = new AdvertiserMenu();
	if (c == '3')
		menu = new AdvertsMenu();

	if( menu != nullptr )
		return menu->run();
}
