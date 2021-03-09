#pragma once

class Zone : public Sprite
{
public:
	Zone(const string& name):
		Sprite(name), isActive(false)
	{
		this->name = "Zone";
	}
	virtual ~Zone()
	{
	}

public:
	virtual void Init()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());

		auto ani = new Animation(spr, 0.1f, true);
		for (size_t i = 0; i < 10; i++)
		{
			ani->AddFrame("Resources/Light/Light_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	virtual void Update()
	{
		Sprite::Update();

		if(isActive)
		{
			color.a = 0.3f;
		}
		else
		{
			color.a = 1.f;
		}
	}


	virtual void Active()
	{
		isActive = true;
		timers.push_back(Timer([&]() { isActive = false; }, 30.f));
	}

public:
	bool isActive;
};

class HealZone : public Zone
{
public:
	HealZone():
		Zone("Resources/Light/Light_0000.png")
	{
	}

	virtual ~HealZone()
	{
	}

public:
	virtual void Init()
	{
		Zone::Init();
	}

	virtual void Update()
	{
		Zone::Update();
	}

	virtual void Active() override;
};

class WeaponZone : public Zone
{
public:
	WeaponZone():
		Zone("Resources/Light/Light_0000.png")
	{
	}

	virtual ~WeaponZone()
	{
	}

public:
	virtual void Init()
	{
		Zone::Init();
	}

	virtual void Update()
	{
		Zone::Update();
	}

	virtual void Active() override;
};