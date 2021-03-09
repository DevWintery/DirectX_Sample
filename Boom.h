#pragma once

class Boom : public Object
{
public:
	Boom::Boom(const Vec2& pos)
	{
		targetPos = pos;
		createRate = 0.3f;
		createTime = 0.f;

		light_1 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Die_Light_1.png"), true, true);

		timers.push_back(Timer([&]()
		{
			light_2 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Die_Light_2.png"), true, true);
			light_2->isNonCamera = true;
			light_2->position = App::GetInstance()->screenSize * 0.5f;
			light_2->scale = Vec2(0.f, 0.f);
			light_2->zOrder = 509;
		}, 3.f));
	}

	Boom::~Boom()
	{
	}

public:
	float createRate;
	float createTime;

	float speed;
	float fadeSpeed;

	Vec2 targetPos;

	shared_ptr<Sprite> light_1;
	shared_ptr<Sprite> light_2;

public:
	virtual void Update() override
	{
		Object::Update();

		light_1->scale += Vec2(App::GetInstance()->deltaTime, App::GetInstance()->deltaTime);
		light_1->position = targetPos;

		if(light_2 != nullptr)
		{
			light_2->scale += Vec2(App::GetInstance()->deltaTime * 8.f, App::GetInstance()->deltaTime * 8.f);
		}

		createTime += App::GetInstance()->deltaTime;
		if (createTime >= createRate)
		{
			createTime = 0.f;

			auto tmp = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Boss_Boom/Boss_Boom_1.png"), true, true);
			tmp->position = targetPos;
			tmp->position.x += rand() % 200 - 100;
			tmp->position.y += rand() % 200 - 100;
			tmp->zOrder = 505;

			auto ani = new Animation(tmp, 0.1f, true);
			for(size_t i = 1; i < 9; i ++)
			{
				ani->AddFrame("Resources/Boss_Boom/Boss_Boom_" + to_string(i) + ".png");
			}
			AnimationManager::GetInstance()->AddAnimation(ani);
		}
	}
};

