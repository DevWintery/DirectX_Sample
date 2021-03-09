#pragma once

template<class T>
class Singleton
{
private:
	static unique_ptr<T> instance;

public:
	Singleton(){}
	virtual ~Singleton(){}

public:
	static T* GetInstance()
	{
		if(!instance)
		{
			instance = unique_ptr<T>(new T());
		}

		return instance.get();
	}
};

template<class T>
unique_ptr<T> Singleton<T>::instance = nullptr;

