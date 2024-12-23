#pragma once
#include <vector>
using namespace std;


class ObjectPool
{
private:
	template <typename T>
	static vector<T*>& getPool()
	{
		static vector<T*> pool;
		return pool;
	}

public :
	template <typename T>
	static T* getObj()
	{
		auto& pool = getPool<T>();
		if (pool.empty()) return new T();
		else
		{
			T* object = pool.back();
			pool.pop_back();
			object->initialize();
			return object;
		}  
	}

	template<typename T>
	static void destroyObj(T* obj)
	{
		obj->reset();
		getPool<T>().emplace_back(obj);
	}
	
};

