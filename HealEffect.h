#pragma once

class HealEffect : public Sprite
{
public:
	HealEffect():
		Sprite("Resources/Hp/Hp_1.png")
	{
	}
	virtual ~HealEffect()
	{
	}

public:
	virtual void Update()
	{
		Sprite::Update();

		position.y -= 1.f;
		color.a -= 0.5f * App::GetInstance()->deltaTime;

		if(color.a <= 0.f)
		{
			isRemoved = true;
		}
	}
};

