#pragma once
#include <fstream>
#include "Pricelist.h"
#include <iostream>
#include "Advertiser.h"

using namespace std;

class Serializer : public fstream
{
public:
	Serializer( string path ) : fstream( path, binary | in | out ) {}

	template <typename T>
	Serializer& write(T & x)
	{
		return static_cast<Serializer&>(fstream::write((char*)&x, sizeof(T)));
	}

	template <typename T>
	Serializer& read(T & x)
	{
		fstream::read((char*)&x, sizeof(x));
		return *this;
	}

	Serializer& write(char* x, size_t size)
	{
		return static_cast<Serializer&>(fstream::write(x, size));
	}

	Serializer& read(char* x, size_t size)
	{
		return static_cast<Serializer&>(fstream::read(x, size));
	}

	/////////////////////////////// SPECIALIZATIONS /////////////////////////////////////

	template <>
	Serializer& write(Advertiser & x)
	{
		write(x.id);
		write(x.name);
		return *this;

	}

	template <>
	Serializer& read(Advertiser & x)
	{
		read(x.id);
		read(x.name);
		return *this;
	}

	template <>
	Serializer& write(Pricelist & x)
	{
		write(x.id);
		write(x.name);
		write((char*)x.getPrices(), 7 * 48 * sizeof(double));
		return *this;

	}

	template <>
	Serializer& read(Pricelist & x)
	{
		read(x.id);
		read(x.name);

		int size = 7 * 48 * sizeof(double);
		double* t = (double*) malloc(size);

		read((char*)t, size);

		x.setPrices(t);

		delete[] t;
		return *this;
	}

	template<>
	Serializer& write(string & x)
	{
		int size = x.size();
		write(size);
		write(const_cast<char*>(x.c_str()), x.size());
		return *this;
	}

	template<>
	Serializer & read( string & x )
	{
		int size;
		read(size);
		char * buff = new char[size+1];
		memset(buff, 0, size+1);
		read(buff, size);
		x = string(buff);
		return *this;
	}
};
