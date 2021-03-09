#pragma once

class ObjectList : public Singleton<ObjectList>
{
private:
	vector<shared_ptr<Object>> objects;
	vector<shared_ptr<Object>> entitys;
	vector<shared_ptr<Object>> uis;
public:
	ObjectList()
	{}
	virtual ~ObjectList()
	{}

public:
	template<class T>
	shared_ptr<T> AddObject(T* obj, bool isEntity = true, bool isUI = false)
	{
		auto tmp = shared_ptr<T>(obj);
		if(isUI)
		{
			uis.push_back(tmp);
		}
		else if(isEntity)
		{
			entitys.push_back(tmp);
		}
		else
		{
			objects.push_back(tmp);
		}

		return tmp;
	}
	
	void Update()
	{
		for(auto it = objects.begin(); it != objects.end();)
		{
			if((*it)->isRemoved)
			{
				it->reset();
				it = objects.erase(it);
			}
			else
			{
				it++;
			}
		}

		for (auto it = entitys.begin(); it != entitys.end();)
		{
			if ((*it)->isRemoved)
			{
				it->reset();
				it = entitys.erase(it);
			}
			else
			{
				it++;
			}
		}
		for (auto it = uis.begin(); it != uis.end();)
		{
			if ((*it)->isRemoved)
			{
				it->reset();
				it = uis.erase(it);
			}
			else
			{
				it++;
			}
		}

		for(size_t i = 0; i < entitys.size(); i ++)
		{
			entitys[i]->Update();
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update();
		}

		for (size_t i = 0; i < uis.size(); i++)
		{
			uis[i]->Update();
		}
	}

	void Draw()
	{
		sort(objects.begin(), objects.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->zOrder < b->zOrder; } );
		sort(entitys.begin(), entitys.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->position.y < b->position.y; });
		sort(uis.begin(), uis.end(), [&](const shared_ptr<Object>& a, const shared_ptr<Object>& b) { return a->zOrder < b->zOrder; });

		for(size_t i = 0; i < objects.size(); i ++)
		{
			if(objects[i]->isVisible)
			{
				objects[i]->Draw();
			}
		}
		for (size_t i = 0; i < entitys.size(); i++)
		{
			if (entitys[i]->isVisible)
			{
				entitys[i]->Draw();
			}
		}
		for (size_t i = 0; i < uis.size(); i++)
		{
			if (uis[i]->isVisible)
			{
				uis[i]->Draw();
			}
		}
	}

	vector<shared_ptr<Object>> GetObjects(const string& name)
	{
		vector<shared_ptr<Object>> v;

		for(auto obj : objects)
		{
			if(obj->name == name)
			{
				v.push_back(obj);
			}
		}

		for (auto obj : entitys)
		{
			if (obj->name == name)
			{
				v.push_back(obj);
			}
		}

		for (auto obj : uis)
		{
			if (obj->name == name)
			{
				v.push_back(obj);
			}
		}

		return v;
	}

	void Release()
	{
		objects.clear();
		entitys.clear();
		uis.clear();
	}
};

