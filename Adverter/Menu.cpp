#include "pch.h"
#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::run()
{
	char c;
	while (true)
	{
		cout << getOptions() << endl;

		cin.clear();
		cin >> c;

		if (c == 'q')
			return;
		
		try {
			handle(c);
		}
		catch (exception * e) {
			cout << "Zle format danych" << endl;
		}
	}
}
