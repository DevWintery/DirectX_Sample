#pragma once

class Snow : public Object
{
public:
	Snow(float _rate, float _speed):
		Object(), createRate(_rate), createTime(0.f), speed(_speed)
	{
		fadeSpeed = 0.15f;
	}
	virtual ~Snow()
	{
		snows.clear();
	}

public:
	vector<shared_ptr<Sprite>> snows;

	float createRate;
	float createTime;
	
	float speed;
	float fadeSpeed;

public:
	virtual void Update()
	{
		Object::Update();

		for(auto it = snows.begin(); it != snows.end();)
		{
			if(0.f >= (*it)->color.a)
			{
				(*it)->isRemoved = true;
				it = snows.erase(it);
			}
			else
			{
				it++;
			}
		}

		createTime += App::GetInstance()->deltaTime;
		if(createTime >= createRate)
		{
			createTime = 0.f;

			auto tmp = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Snow.png"), true, true);
			tmp->position = Vec2( rand() % static_cast<int>(App::GetInstance()->screenSize.x) , 0.f);
			tmp->isNonCamera = true;
			tmp->zOrder = 505;

			tmp->color = Color(Random(), Random(), Random(), Random());

			snows.push_back(tmp);
		}

		for(size_t i = 0; i < snows.size(); i ++)
		{
			snows[i]->position.y += speed * App::GetInstance()->deltaTime;
			snows[i]->color.a -= fadeSpeed * App::GetInstance()->deltaTime;
		}
	}

	float Random()	
	{
		float random = (float)rand() / (float)RAND_MAX;

		return random;
	}
};

