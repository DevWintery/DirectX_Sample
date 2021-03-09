#pragma once

class Smoke : public Sprite
{
public:
	Smoke():
		Sprite("Resources/Smoke/Smoke_1.png")
	{
	}
	virtual ~Smoke()
	{}

public:
	Animation* ani;

public:
	void Init()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());

		ani = new Animation(spr, 0.1f, false);

		for(size_t i = 0; i < 6; i ++)
		{
			ani->AddFrame("Resources/Smoke/Smoke_" + to_string(i + 1) + ".png");
		}

		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	virtual void Update()
	{
		Sprite::Update();

		if(ani->isDone)
		{
			isRemoved = true;
		}
	}
};

