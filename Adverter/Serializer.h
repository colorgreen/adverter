#pragma once
#include <fstream>
#include "Pricelist.h"
#include <iostream>
#include "Advertiser.h"
#include "Spot.h"

using namespace std;

class Serializer : public fstream
{
public:
	Serializer(string path) : fstream(path, binary | in | out)
	{
	}

	template <typename T>
	Serializer& write(T& x)
	{
		return static_cast<Serializer&>(fstream::write((char*)&x, sizeof(T)));
	}

	template <typename T>
	Serializer& read(T& x)
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
	Serializer& write(Spot& x)
	{
		write(x.id);
		write(x.name);
		write(x.price);
		write(x.id_advertiser);
		write(x.period);
		write(x.day);
		write(x.duration);
		return *this;
	}

	template <>
	Serializer& read(Spot& x)
	{
		read(x.id);
		read(x.name);
		read(x.price);
		read(x.id_advertiser);
		read(x.period);
		read(x.day);
		read(x.duration);
		return *this;
	}

	template <>
	Serializer& write(Advertiser& x)
	{
		write(x.id);
		write(x.name);
		return *this;
	}

	template <>
	Serializer& read(Advertiser& x)
	{
		read(x.id);
		read(x.name);
		return *this;
	}

	template <>
	Serializer& write(Pricelist& x)
	{
		write(x.id);
		write(x.name);
		write((char*)x.getPrices(), 7 * 48 * sizeof(double));
		for (int i = 5; i <= 60; i += 5)
			write(x.factors[i]);
		return *this;
	}

	template <>
	Serializer& read(Pricelist& x)
	{
		read(x.id);
		read(x.name);

		int size = 7 * 48 * sizeof(double);
		double* t = (double*)malloc(size);
		read((char*)t, size);
		x.setPrices(t);
		delete[] t;

		double tmp;
		for (int i = 5; i <= 60; i += 5)
		{
			read(tmp);
			x.factors[i] = tmp;
		}

		return *this;
	}

	template <>
	Serializer& write(string& x)
	{
		int size = x.size();
		write(size);
		write(const_cast<char*>(x.c_str()), x.size());
		return *this;
	}

	template <>
	Serializer& read(string& x)
	{
		int size;
		read(size);
		char* buff = new char[size + 1];
		memset(buff, 0, size + 1);
		read(buff, size);
		x = string(buff);
		return *this;
	}

	template <typename T>
	Serializer& write(DatabaseObjects<T>& v)
	{
		int size = v.size();
		write(size);
		for (auto a : v)
			write(*a);
		return *this;
	}

	template <typename T>
	Serializer& read(DatabaseObjects<T*>& v)
	{
		int size = 0;
		read(size);
		for (int i = 0; i < size; i++)
		{
			T *t = new T();
			read(*t);
			v.push_back(t);
		}
		return *this;
	}
};
