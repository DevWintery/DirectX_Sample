#pragma once

class HpBar : public ProgressBar
{
public:
	HpBar():
		ProgressBar("Resources/Hp_2.png")
	{
		background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hp_1.png"), true, true);
	}
	virtual ~HpBar()
	{}

public:
	virtual void Update()
	{
		ProgressBar::Update();

		background->position = position;
		background->zOrder = zOrder - 1;
	}

	void Remove()
	{
		isRemoved = true;
		background->isRemoved = true;
	}

public:
	shared_ptr<Sprite> background;
};

class PlayerHpBar : public ProgressBar
{
public:
	PlayerHpBar() :
		ProgressBar("Resources/Hp_Bar_1.png")
	{
		background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hp_Bar_2.png"), true, false);
	}
	virtual ~PlayerHpBar()
	{}

public:
	virtual void Update()
	{
		ProgressBar::Update();

		background->position = position;
		background->zOrder = zOrder - 1;
		background->isNonCamera = true;
	}

	void Remove()
	{
		isRemoved = true;
		background->isRemoved = true;
	}

public:
	shared_ptr<Sprite> background;
};

class PlayerStaminaBar : public ProgressBar
{
public:
	PlayerStaminaBar() :
		ProgressBar("Resources/Sp_2.png")
	{
		background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Sp_1.png"), true, false);
	}
	virtual ~PlayerStaminaBar()
	{}

public:
	virtual void Update()
	{
		ProgressBar::Update();

		background->position = Vec2(position.x, position.y);
		background->zOrder = zOrder - 1;
		background->isNonCamera = true;
	}

	void Remove()
	{
		isRemoved = true;
		background->isRemoved = true;
	}

public:
	shared_ptr<Sprite> background;
};