#pragma once
#include "DatabaseModel.h"
#include <iostream>
#include <vector>

using namespace std;

class Advertiser
{
	string name;
public:
	TABLE(Advertiser)

	Advertiser();
	~Advertiser();

	void setName(string name);

	string getName() { return name; }
};


