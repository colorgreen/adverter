#pragma once
#include <string>

class Menu
{
protected:
	std::string options;

public:

	void run();

	std::string getOptions() { return options; }

	virtual void handle(char c) = 0;
};

