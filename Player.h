#pragma once

class Player : public Sprite
{
public:
	enum STATE
	{
		IDLE,
		WALK,
		RUN,
		ATTACK,
		DIE,
		SIZE
	};

	enum WEAPON
	{
		RIFLE,
		LAZER,
		WEAPONSIZE,
	};
public:
	Player():
		Sprite("Resources/Player/1.png"), state(IDLE), dir(0), stateStr { "Idle", "Walk", "Run", "Attack", "Die" }, weaponStr { "Rifle", "Lazer" }, weapon(RIFLE), attackTime(0.f), attackRate(0.3f), smokeTime(0.f), smokeRate(0.5f)
	{
		name = "Player";

		speed = 200.f;
		curSpeed = speed;

		hp = 100.f;
		maxHp = hp;

		stamina = 100.f;
		maxStamina = stamina;

		shadow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Player/Shadow.png"), false);
		_shadow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Under_Light1.png"), false);

		_shadow->scale *= 0.5f;

		isStart = true;
	}
	virtual ~Player()
	{}
	 
public:
	float speed;
	float curSpeed;
	
	STATE state;
	string stateStr[SIZE];
	
	WEAPON weapon;
	string weaponStr[WEAPONSIZE];
	
	map<string, Animation*> animations;
	
	shared_ptr<Sprite> shadow;
	shared_ptr<Sprite> _shadow;
	
	shared_ptr<Sprite> hitSpr;
	shared_ptr<Animation> hitAni;

	int dir;

	bool isStart;

	float hp;
	float maxHp;
	
	float stamina;
	float maxStamina;

	float attackRate;
	float attackTime;
	
	float smokeRate;
	float smokeTime;
public:
	void Init()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());

		for(size_t w = 0; w < WEAPONSIZE; w ++)
		{
			for(size_t i = 0; i < 4; i ++)
			{
				auto idleAni = AddAnimation(weaponStr[w] + stateStr[IDLE] + to_string(i), spr, 0.08f);
				auto walkAni = AddAnimation(weaponStr[w] + stateStr[WALK] + to_string(i), spr, 0.05f);
				auto runAni = AddAnimation(weaponStr[w] + stateStr[RUN] + to_string(i), spr, 0.025f);
				auto attackAni = AddAnimation(weaponStr[w] + stateStr[ATTACK] + to_string(i), spr, 0.05f);
				auto dieAni = AddAnimation(weaponStr[w] + stateStr[DIE] + to_string(i), spr, 0.05f);
				dieAni->loop = false;
				for(size_t idle = 0; idle < 20; idle ++)
				{
					idleAni->AddFrame("Resources/Player/" + weaponStr[w] + "/" + to_string(i + 1) + "/" + "Ct_Idle_" + to_string( ((i+1) * 10000) + idle) + ".png");
				}

				for (size_t walk = 95; walk < 115; walk++)
				{
					walkAni->AddFrame("Resources/Player/" + weaponStr[w] + "/" + to_string(i + 1) + "/" + "Ct_Walk_" + to_string(((i + 1) * 10000) + walk) + ".png");
				}

				for(size_t run = 25; run < 45; run ++)
				{
					runAni->AddFrame("Resources/Player/" + weaponStr[w] + "/" + to_string(i + 1) + "/" + "Ct_Run_" + to_string(((i + 1) * 10000) + run) + ".png");
				}

				for(size_t attack = 120; attack < 140; attack ++)
				{
					attackAni->AddFrame("Resources/Player/" + weaponStr[w] + "/" + to_string(i + 1) + "/" + "Ct_Attack_" + to_string(((i + 1) * 10000) + attack) + ".png");
				}

				for (size_t die = 150; die < 166; die++)
				{
					dieAni->AddFrame("Resources/Player/" + weaponStr[w] + "/" + to_string(i + 1) + "/" + "Ct_Die_" + to_string(((i + 1) * 10000) + die) + ".png");
				}
			}
		}
	}

	Animation* AddAnimation(const string& key, shared_ptr<Sprite> spr, float rate)
	{
		auto ani = animations[key] = new Animation(spr, rate, true);
		ani->isStop = true;

		AnimationManager::GetInstance()->AddAnimation(ani);

		return ani;
	}

	virtual void Update();

	void CreateSmoke();

	void Move()
	{
		state = WALK;

		if(DXUTIsKeyDown(VK_SHIFT) && stamina > 0.f)
		{
			state = RUN;
			
			if (0.f < stamina)
			{
				stamina -= 4 * App::GetInstance()->deltaTime;
			}
			curSpeed = speed * 1.5f;
		}
		else
		{
			curSpeed = speed;
		}

		Vec2 pos = position;
		if (DXUTIsKeyDown('W'))
		{
			pos.y -= curSpeed * App::GetInstance()->deltaTime;

			dir = 0;
		}

		else if (DXUTIsKeyDown('A'))
		{
			pos.x -= curSpeed * App::GetInstance()->deltaTime;

			dir = 3;
		}


		else if (DXUTIsKeyDown('D'))
		{
			pos.x += curSpeed * App::GetInstance()->deltaTime;

			dir = 1;
		}

		else if (DXUTIsKeyDown('S'))
		{
			pos.y += curSpeed * App::GetInstance()->deltaTime;

			dir = 2;
		}

		int i = 0;
		auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");
		for(auto ob : obstacle)
		{
			auto spr = dynamic_pointer_cast<Sprite>(ob);
			if(Rect::CollisionPoint(spr->GetRect(), pos))
			{
				i++;
			}

			if(Rect::CollisionRect(spr->GetRect(), GetRect()))
			{
				if (spr->position.y > position.y)
				{
					spr->color.a = 0.5f;
				}
			}
			else
			{
				spr->color.a = 1.f;
			}
		}

		if(i > 0)
		{

		}
		else
		{
			position = pos;
		}
	}

	void Attack();

	void AllStopAnimation()
	{
		for(auto ani : animations)
		{
			ani.second->isStop = true;
		}
	}

	virtual RECT GetRect()
	{
		RECT r = Rect::Tex2SprTex(this);
		
		r.left += 150.f;
		r.right -= 150.f;
		r.top += 80.f;
		r.bottom -= 80.f;

		return r;
	}
};

