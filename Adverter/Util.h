#pragma once
#include <iostream>
#include <string>

using namespace std;

class Util
{
public:
	
	template<typename T>
	static T input( string message )
	{
		T t;
		cout << message << ": ";
		cin >> t;
		cout << endl;
		return t;
	}
};

