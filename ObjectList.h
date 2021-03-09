#pragma once

class ObjectList : public Singleton<ObjectList>
{
public:
	ObjectList();
	virtual ~ObjectList();

public:
	vector<shared_ptr<Object>> objects;

public:
	template<class T>
	shared_ptr<T> AddObject(T* object)
	{
		auto tmp = shared_ptr<T>(object);
		objects.push_back(tmp);

		return tmp;
	}

	template<class T>
	void RemoveObject(shared_ptr<T>& p)
	{
		p->Remove();
		p = nullptr;
	}

	vector<shared_ptr<Object>> GetObjects(const string& name)
	{
		vector<shared_ptr<Object>> tmp;
		for (auto it = objects.begin(); it != objects.end(); it++)
		{
			if ((*it)->name == name)
			{
				tmp.push_back((*it));
			}
		}

		return tmp;
	}

	void DrawObjects()
	{
		sort(objects.begin(), objects.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->zOrder < b->zOrder; });

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects[i]->isVisible && App::GetInstance()->sprite != nullptr)
			{
				objects[i]->Draw();
			}
		}
	}

	void Update()
	{
		for (auto it = objects.begin(); it != objects.end();)
		{
			if ((*it)->isRemoved && !(*it)->donDestory)
			{
				(*it).reset();
				it = objects.erase(it);
			}
			else
			{
				it++;
			}
		}


		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update();
		}
	}

	void Release()
	{
		for (auto it = objects.begin(); it != objects.end();)
		{
			if (!(*it)->donDestory)
			{
				(*it).reset();
				it = objects.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
};