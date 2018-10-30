#pragma once
#include <vector>
#include <algorithm>
#include <functional>

using namespace  std;

template<typename T>
class DatabaseObjects :
	public vector<T>
{
public:

	template<typename T>
	DatabaseObjects<T> where(function<bool(T)> condition)
	{
		DatabaseObjects<T> v;
		if (this->size() == 0)
			return v;

		for (T t : *this)
		{
			if (condition(t))
				v.push_back(t);
		}
		return v;
	}

	template<typename T, typename SUMT>
	SUMT sum(function<SUMT(T)> property)
	{
		SUMT sum = 0;
		if (this->size() == 0)
			return sum;

		for (T t : *this)
			sum += property(t);
		return sum;
	}

	template<typename T>
	T* single(function<bool(T*)> condition)
	{
		for (T* t : T::table)
			if (condition(t))
				return t;
		return nullptr;
	}

	template<typename T>
	int count(function<bool(T)>& condition)
	{
		auto v = where(condition);
		return v.size();
	}

	int count()
	{
		return this->size();
	}

	template<typename T>
	auto all()
	{
		return this;
	}

};

