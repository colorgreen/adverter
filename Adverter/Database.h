#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include "Pricelist.h"
#include "Advertiser.h"
#include "Serializer.h"

using namespace std;

class Database
{
	const std::string filename = "database.dat";

	static Database* instance;

	bool create();

public:

	bool load() const;
	bool save() const;
	void reset() const;

	template <typename T>
	T* newObject()
	{
		DatabaseModel* t = new T();
		t->setId(T::newId++);
		return (T*)t;
	}

	template <typename T>
	void add(T* t)
	{
		T::table.push_back(t);
	}

	template<typename T>
	void remove(T*t)
	{
		int i = 0;
		for (;i < T::table.size(); i++)
			if (T::table[i] == t)
				break;
		delete t;
		T::table.erase(T::table.begin() + i);
	}

	template<typename T>
	DatabaseObjects<T*>& get()
	{
		return T::table;
	}

	static Database* getContext();

	//	template<typename T>
	//	int getNewId() { return T::newId; }
};
