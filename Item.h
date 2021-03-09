#pragma once

class Item : public Sprite
{
public:
	Item(const string& name):
		Sprite(name)
	{}
	virtual ~Item()
	{}

public:
	shared_ptr<Sprite> light;

public:
	virtual void Init()
	{
		light = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Item_Light/Item_Light00.png"), false);

		auto ani = new Animation(light, 0.1f, true);
		for(size_t i = 0; i < 11; i ++)
		{
			ani->AddFrame("Resources/Item_Light/Item_Light0" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	virtual void Update()
	{
		Sprite::Update();

		light->position = position;

		auto player = ObjectList::GetInstance()->GetObjects("Player");
		for(auto pyr : player)
		{
			auto spr = dynamic_pointer_cast<Sprite>(pyr);
			if(Rect::CollisionPoint(GetRect(), spr->position) && isVisible)
			{
				Effect();
				isVisible = false;
				light->isRemoved = true;
			}
		}

	}

	virtual void Effect()
	{
	}
};

class HpUpItem : public Item
{
public:
	HpUpItem():
		Item("Resources/Item/Hp/Item_Hp_0000.png")
	{
	}

	virtual ~HpUpItem()
	{
	}

public:
	virtual void Init()
	{
		Item::Init();

		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		auto ani = new Animation(spr, 0.1f, true);

		for (size_t i = 0; i < 10; i++)
		{
			ani->AddFrame("Resources/Item/Hp/Item_Hp_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	virtual void Effect();
};

class TimeItem : public Item
{
public:
	TimeItem():
		Item("Resources/Item/Time/Item_Time_0000.png")
	{
	}
	
	virtual ~TimeItem()
	{
	}

public:
	virtual void Init()
	{
		Item::Init();

		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		auto ani = new Animation(spr, 0.1f, true);

		for (size_t i = 0; i < 10; i++)
		{
			ani->AddFrame("Resources/Item/Time/Item_Time_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}
	
	virtual void Effect();
};

class WeaponItem : public Item
{

public:
	WeaponItem() :
		Item("Resources/Item/Weapon/Item_Weapone_0000.png")
	{
	}

	virtual ~WeaponItem()
	{
	}

public:
	virtual void Init()
	{
		Item::Init();

		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		auto ani = new Animation(spr, 0.1f, true);

		for (size_t i = 0; i < 10; i++)
		{
			ani->AddFrame("Resources/Item/Weapon/Item_Weapone_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	virtual void Effect();
};