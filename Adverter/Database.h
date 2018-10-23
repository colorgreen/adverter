#pragma once
#include <string>
#include <vector>
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

	template <typename T>
	void saveTable(Serializer& file) const
	{
		int size = T::table.size();
		file.write(size);

		for (T * t : T::table)
			file.write(*t);
	
	}

	template <typename T>
	void loadTable(Serializer& file) const
	{
		int size = 0;
		file.read(size);

		for(int i=0; i<size; i++)
		{
			T * t = new T();
			file.read(*t);
			T::table.push_back(t);
		}

	}

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
	vector<T*> where(function<bool(T*)>& condition )
	{
		vector<T*> v;
		for (T* t : T::table)
			if (condition(t))
				v.push_back(t);
		return v;
	}

	template<typename T>
	auto all()
	{
		return T::table;
	}

	template<typename T>
	T* single( function<bool(T*)>& condition)
	{
		vector<T*> v;
		for (T* t : T::table)
			if (condition(t))
				return t;
		return nullptr;
	}

	static Database* getContext();

	//	template<typename T>
	//	int getNewId() { return T::newId; }
};
