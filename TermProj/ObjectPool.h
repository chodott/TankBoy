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
	static T* getObj(float x, float y, float z)
	{
		auto& pool = getPool<T>();
		if (pool.empty()) return new T(x,y,z);
		else
		{
			T* object = pool.back();
			pool.pop_back();
			object->initialize(x,y,z);
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

