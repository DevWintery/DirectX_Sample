#pragma once

class Bullet : public Sprite
{
public:
	Bullet(const string& name, const Vec2& pos, int _dir):
		Sprite(name), dir(_dir), dirVec(0.f, 0.f), isDie(false), dieAni(nullptr)
	{
		speed = 1500.f;
		damage = 10.f;
		
		position = pos;

		zOrder = 0;
	}
	virtual ~Bullet()
	{}
	
public:
	int dir;
	Vec2 dirVec;

	float speed;
	float damage;

	bool isDie;
	Animation* dieAni;

public:
	virtual void Update()
	{
		Sprite::Update();

		auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");
		for (auto ob : obstacle)
		{
			auto spr = dynamic_pointer_cast<Sprite>(ob);
			if (Rect::CollisionPoint(spr->GetRect(), position))
			{
				isRemoved = true;
			}
		}

		switch(dir)
		{
		case 0: dirVec = { 0.f, -1.f }; break;
		case 1: dirVec = { 1.f, 0.f }; break;
		case 2: dirVec = { 0.f, 1.f }; break;
		case 3: dirVec = { -1.f, 0.f }; break;
		}

		if(isDie)
		{
			if(dieAni == nullptr)
			{
				isRemoved = true;
			}
			else
			{
				if(dieAni->isDone)
				{
					isRemoved = true;
				}
			}
		}
		else
		{
			position += dirVec * speed * App::GetInstance()->deltaTime;
		}
	}

	virtual void Die()
	{
		isDie = true;
	}
};

class NormalBullet : public Bullet
{
public:
	NormalBullet(const Vec2& pos, int _dir):
		Bullet("Resources/Bullet.png", pos, _dir)
	{
		name = "Bullet";

		speed = 800.f;

		if (dir == 0)
		{
			position.x += 20.f;
		}

		if (dir == 1)
		{
			position.y += 20.f;
		}

		if (dir == 2)
		{
			position.x -= 20.f;
		}
		if (dir == 3)
		{
			position.y -= 20.f;
		}
	}

	virtual ~NormalBullet()
	{}


public:
	virtual void Update()
	{
		Bullet::Update();
	}

	virtual void Die()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		dieAni = new Animation(spr, 0.05f, false);

		for (size_t i = 0; i < 5; i++)
		{
			dieAni->AddFrame("Resources/Bullet_Hit/Bullet_Hit_" + to_string(i + 1) + ".png");
		}

		AnimationManager::GetInstance()->AddAnimation(dieAni);

		isDie = true;
	}
};

class LazerBullet : public Bullet
{
public:
	LazerBullet(const Vec2& pos, int _dir) :
		Bullet("Resources/Razer_Bullet.png", pos, _dir)
	{
		name = "Bullet";

		speed = 3000.f;

		if (dir == 0)
		{
			rotation = D3DXToRadian(90);
		}

		if (dir == 2)
		{
			rotation = D3DXToRadian(-90);
		}
	}

	virtual ~LazerBullet()
	{}


public:
	virtual void Update()
	{
		Bullet::Update();
	}

	virtual void Die()
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		dieAni = new Animation(spr, 0.05f, false);

		for (size_t i = 0; i < 5; i++)
		{
			dieAni->AddFrame("Resources/Bullet_Hit2/Bullet_Hit2_" + to_string(i + 1) + ".png");
		}

		AnimationManager::GetInstance()->AddAnimation(dieAni);

		isDie = true;
	}
};

class Enemy_1_Bullet : public Bullet
{
public:
	Enemy_1_Bullet(const Vec2& pos, int _dir) :
		Bullet("Resources/Monster1_Bullet.png", pos, _dir)
	{
		name = "EnemyBullet";
	}

	virtual ~Enemy_1_Bullet()
	{}


public:
	virtual void Update()
	{
		Bullet::Update();
	}
};

class Enemy_2_Bullet : public Bullet
{
public:
	Enemy_2_Bullet(const Vec2& pos, int _dir) :
		Bullet("Resources/Monster2_Bullet.png", pos, _dir)
	{
		name = "EnemyBullet";
	}

	virtual ~Enemy_2_Bullet()
	{}


public:
	virtual void Update()
	{
		Bullet::Update();
	}
};