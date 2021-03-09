#pragma once

class HpBar;

class Enemy : public Sprite
{
public:
	enum STATE
	{
		MOVE,
		ATTACK,
		SIZE
	};
public:
	Enemy(const string& name);
	virtual ~Enemy()
	{}

public:
	bool isDie;

	float speed;
	float curSpeed;

	float hp;
	float maxHp;

	shared_ptr<HpBar> hpBar;
	shared_ptr<Sprite> shadow;

	int dir;
	Vec2 dirVec;

	STATE state;
	string stateStr[SIZE];

	float moveRate;
	float moveTime;

	float attackRate;
	float attackTime;

	map<string, Animation*> animations;

	float dis;

public:
	Animation* AddAnimation(const string& key, shared_ptr<Sprite> spr, float rate)
	{
		auto ani = animations[key] = new Animation(spr, rate, true);
		ani->isStop = true;

		AnimationManager::GetInstance()->AddAnimation(ani);

		return ani;
	}

public:
	virtual void Init();
	virtual void Update();
	virtual void Die();
};

class Enemy_1 : public Enemy
{
public:
	Enemy_1():
		Enemy("Resources/Enemy/1/1/Monster1_Move_11.png")
	{
		maxHp = 200.f;
		hp = maxHp;

		shadow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Enemy/1/Shadow.png"), false);
	}
	virtual ~Enemy_1()
	{
	}

public:

public:
	virtual void Init()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());

		for (size_t i = 0; i < 4; i++)
		{
			auto moveAni = AddAnimation(stateStr[MOVE] + to_string(i), spr, 0.08f);
			moveAni->AddFrame("Resources/Enemy/1/" + to_string(i + 1 ) + "/Monster1_Move_" + to_string(i + 1) + "1.png");
			moveAni->AddFrame("Resources/Enemy/1/" + to_string(i + 1) + "/Monster1_Move_" + to_string(i + 1) + "2.png");

			auto attackAni = AddAnimation(stateStr[ATTACK] + to_string(i), spr, 0.08f);
			attackAni->AddFrame("Resources/Enemy/1/" + to_string(i + 1) + "/Monster1_Attack_" + to_string(i + 1) + "1.png");
			attackAni->AddFrame("Resources/Enemy/1/" + to_string(i + 1) + "/Monster1_Attack_" + to_string(i + 1) + "2.png");
		}
	}

	virtual void Update();

	virtual RECT GetRect() override
	{
		RECT r = Rect::Tex2SprTex(this);
		
		r.right -= 100.f;
		r.left += 100.f;
		r.bottom -= 100.f;
		r.top += 100.f;

		return r;
	}
};

class Enemy_2 : public Enemy
{
public:
	Enemy_2() :
		Enemy("Resources/Enemy/2/1/Monster2_Move_10000.png")
	{
		maxHp = 200.f;
		hp = maxHp;

		shadow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Enemy/2/Shadow.png"), false);
	}

	virtual ~Enemy_2()
	{
	}

public:
	virtual void Init()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());

		for (size_t i = 0; i < 4; i++)
		{
			auto moveAni = AddAnimation(stateStr[MOVE] + to_string(i), spr, 0.08f);
			for(size_t move = 0; move < 8; move ++)
			{
				moveAni->AddFrame("Resources/Enemy/2/" + to_string(i +1) + "/Monster2_Move_" + to_string( (i + 1) * 10000 + move) + ".png");
			}

			auto attackAni = AddAnimation(stateStr[ATTACK] + to_string(i), spr, 0.08f);
			for (size_t attack = 9; attack < 15; attack++)
			{
				attackAni->AddFrame("Resources/Enemy/2/" + to_string(i + 1) + "/Monster2_Attack_" + to_string((i + 1) * 10000 + attack) + ".png");
			}
		}
	}

	virtual void Update();

	virtual RECT GetRect();
};

class Boss : public Enemy
{
public:
	Boss() :
		Enemy("Resources/Boss/1/Boss_Move_B_10000.png")
	{
		maxHp = 1000.f;
		hp = maxHp;

		dis= 600.f;
	}

	virtual ~Boss()
	{
	}

public:
	shared_ptr<Sprite> head;
	shared_ptr<Sprite> shiled;

public:
	virtual void Init()
	{
		head = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Boss/1/Boss_Move_H_1.png"), true, true);

		shiled = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Boss_Shiled/Shiled_0000.png"), true, true);

		auto ani = new Animation(shiled, 0.1f, true);
		for(size_t i = 0; i < 10; i ++)
		{
			ani->AddFrame("Resources/Boss_Shiled/Shiled_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);

		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		for (size_t i = 0; i < 4; i++)
		{
			auto moveAni = AddAnimation(stateStr[MOVE] + to_string(i), spr, 0.1f);
			for (size_t move = 0; move < 10; move++)
			{
				moveAni->AddFrame("Resources/Boss/" + to_string(i + 1) + "/Boss_Move_B_" + to_string((i + 1) * 10000 + move) + ".png");
			}

			auto attackAni = AddAnimation(stateStr[ATTACK] + to_string(i), head, 0.1f);
			for (size_t attack = 0; attack < 10; attack++)
			{
				attackAni->AddFrame("Resources/Boss/" + to_string(i + 1) + "/Boss_Attack_H_" + to_string((i + 1) * 10000 + attack) + ".png");
			}
		}
	}

	virtual void Update();

	virtual RECT GetRect();
	virtual void Die();
};