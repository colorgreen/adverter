#pragma once
#include "DatabaseModel.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Advertiser : public DatabaseModel
{
public:
	TABLE(Advertiser)

	friend ostream& operator<<(ostream& output, const Advertiser& p);

	void setName(string name);

	auto getName() const { return name; }

private:
	friend class Serializer;

	string name;
};


