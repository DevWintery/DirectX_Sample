#include "DXUT.h"
#include"Precompile.h"
#include "Enemy.h"
#include"HpBar.h"
#include"Bullet.h"
#include"Player.h"
#include"Item.h"
#include"GameManager.h"
#include"Outro.h"
#include"Boom.h"

Enemy::Enemy(const string & name):
	Sprite(name), dir(rand() % 4), state(MOVE), moveTime(0.f), moveRate(3.f), attackTime(0.f), attackRate(0.5f), stateStr{"Move", "Attack"}, isDie(false)
{
	speed = 100.f;
	curSpeed = speed;

	maxHp = 100.f;
	hp = maxHp;

	hpBar = ObjectList::GetInstance()->AddObject(new HpBar(), true, true);

	dis = 300.f;
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	Sprite::Update();

	hpBar->SetValue(hp / maxHp);
	hpBar->zOrder = zOrder + 2;

	if(shadow != nullptr)
	{
		shadow->position = Vec2(position.x, position.y + 50.f);
		shadow->zOrder = zOrder;
	}

	auto bullets = ObjectList::GetInstance()->GetObjects("Bullet");
	for (auto bullet : bullets)
	{
		auto spr = dynamic_pointer_cast<Bullet>(bullet);

		RECT r = GetRect();

		if (Rect::CollisionPoint(r, spr->position))
		{
			if (!spr->isDie)
			{
				spr->Die();
				hp -= 10.f;
			}
		}
	}

	if (0 >= hp)
	{
		Die();
		isDie = true;
	}

	if (GameManager::GetInstance()->isStop) { return; }

	auto player = ObjectList::GetInstance()->GetObjects("Player");
	for(auto pyr : player)
	{
		auto spr = dynamic_pointer_cast<Player>(pyr);

		Vec2 d = spr->position - position;
		if(D3DXVec2Length(&d) < dis && spr->state != Player::DIE)
		{
			D3DXVec2Normalize(&dirVec, &d);
			state = ATTACK;
		}
		else
		{
			state = MOVE;
		}
	}


	for (auto ani : animations)
	{
		if(ani.second != nullptr)
		{
			ani.second->isStop = true;
		}
	}

	if(animations[stateStr[state] + to_string(dir)] != nullptr)
	{
		animations[stateStr[state] + to_string(dir)]->isStop = false;
	}
}

void Enemy::Die()
{
	int drop = rand() % 1;
	if(drop == 0)
	{
		int type = rand() % 3;
		switch(type)
		{
		case 0:
		{
			auto hp = ObjectList::GetInstance()->AddObject(new HpUpItem());
			hp->position = position;
			hp->Init();
		}
			break;
		case 1:
		{
			auto time = ObjectList::GetInstance()->AddObject(new TimeItem());
			time ->position = position;
			time->Init();
		}
			break;
		case 2:
		{
			auto weapon = ObjectList::GetInstance()->AddObject(new WeaponItem());
			weapon->position = position;
			weapon->Init();
		}
			break;
		}
	}

	if(shadow != nullptr)
	{
		shadow->isRemoved = true;
	}
	hpBar->Remove();
	isRemoved = true;
}

void Enemy_1::Update()
{
	Enemy::Update();

	if (GameManager::GetInstance()->isStop) { return; }

	if (state == ATTACK)
	{
		attackTime += App::GetInstance()->deltaTime;
		if (attackTime >= attackRate)
		{
			attackTime = 0.f;

			Vec2 v = abs(dirVec.x) > abs(dirVec.y) ? Vec2(round(dirVec.x), 0.f) : Vec2(0.f, round(dirVec.y));
			if (v.x == 1 && v.y == 0)
			{
				dir = 1;
			}
			else if (v.x == -1 && v.y == 0)
			{
				dir = 3;
			}
			else if (v.x == 0 && v.y == 1)
			{
				dir = 2;
			}
			else if (v.x == 0 && v.y == -1)
			{
				dir = 0;
			}

			ObjectList::GetInstance()->AddObject(new Enemy_1_Bullet(position, dir));
		}
	}

	else if (state == MOVE)
	{
		moveTime += App::GetInstance()->deltaTime;
		if (moveTime >= moveRate)
		{
			moveTime = 0.f;
			dir = rand() % 4;
		}
		switch (dir)
		{
		case 0:
			dirVec = { 0.f, -1.f };
			break;
		case 1:
			dirVec = { 1.f, 0.f };
			break;
		case 2:
			dirVec = { 0.f, 1.f };
			break;
		case 3:
			dirVec = { -1.f, 0.f };
			break;
		}

		Vec2 pos = position + dirVec * curSpeed * App::GetInstance()->deltaTime;

		int i = 0;
		auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");
		for (auto ob : obstacle)
		{
			auto spr = dynamic_pointer_cast<Sprite>(ob);
			if (Rect::CollisionPoint(spr->GetRect(), pos))
			{
				i++;
			}
		}

		if (i > 0)
		{
		}
		else
		{
			position = pos;
		}
	}

	hpBar->position = Vec2(position.x, position.y - 100.f);
}

void Enemy_2::Update()
{
	Enemy::Update();

	if (GameManager::GetInstance()->isStop) { return; }

	if (state == ATTACK)
	{
		attackTime += App::GetInstance()->deltaTime;
		if (attackTime >= attackRate)
		{
			attackTime = 0.f;

			Vec2 v = abs(dirVec.x) > abs(dirVec.y) ? Vec2(round(dirVec.x), 0.f) : Vec2(0.f, round(dirVec.y));
			if (v.x == 1 && v.y == 0)
			{
				dir = 1;
			}
			else if (v.x == -1 && v.y == 0)
			{
				dir = 3;
			}
			else if (v.x == 0 && v.y == 1)
			{
				dir = 2;
			}
			else if (v.x == 0 && v.y == -1)
			{
				dir = 0;
			}

			ObjectList::GetInstance()->AddObject(new Enemy_2_Bullet(position, dir));
		}
	}

	else if (state == MOVE)
	{
		moveTime += App::GetInstance()->deltaTime;
		if (moveTime >= moveRate)
		{
			moveTime = 0.f;
			dir = rand() % 4;
		}
		switch (dir)
		{
		case 0:
			dirVec = { 0.f, -1.f };
			break;
		case 1:
			dirVec = { 1.f, 0.f };
			break;
		case 2:
			dirVec = { 0.f, 1.f };
			break;
		case 3:
			dirVec = { -1.f, 0.f };
			break;
		}

		Vec2 pos = position + dirVec * curSpeed * App::GetInstance()->deltaTime;

		int i = 0;
		auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");
		for (auto ob : obstacle)
		{
			auto spr = dynamic_pointer_cast<Sprite>(ob);
			if (Rect::CollisionPoint(spr->GetRect(), pos))
			{
				i++;
			}
		}

		if (i > 0)
		{
		}
		else
		{
			position = pos;
		}
	}
	hpBar->position = Vec2(position.x, position.y - 200.f);
}

RECT Enemy_2::GetRect()
{
	RECT r;

	r = Rect::Tex2SprTex(this);

	r.right -= 200.f;
	r.left += 200.f;
	r.bottom -= 200.f;
	r.top += 200.f;

	return r;
}

void Boss::Update()
{
	Enemy::Update();


	if (state == ATTACK)
	{
		attackTime += App::GetInstance()->deltaTime;
		if (attackTime >= attackRate)
		{
			attackTime = 0.f;

			Vec2 v = abs(dirVec.x) > abs(dirVec.y) ? Vec2(round(dirVec.x), 0.f) : Vec2(0.f, round(dirVec.y));
			if (v.x == 1 && v.y == 0)
			{
				dir = 1;
			}
			else if (v.x == -1 && v.y == 0)
			{
				dir = 3;
			}
			else if (v.x == 0 && v.y == 1)
			{
				dir = 2;
			}
			else if (v.x == 0 && v.y == -1)
			{
				dir = 0;
			}

			ObjectList::GetInstance()->AddObject(new Enemy_2_Bullet(position, dir));
		}
	}

	else if (state == MOVE)
	{
		moveTime += App::GetInstance()->deltaTime;
		if (moveTime >= moveRate)
		{
			moveTime = 0.f;
			dir = rand() % 4;
		}
		switch (dir)
		{
		case 0:
			dirVec = { 0.f, -1.f };
			break;
		case 1:
			dirVec = { 1.f, 0.f };
			break;
		case 2:
			dirVec = { 0.f, 1.f };
			break;
		case 3:
			dirVec = { -1.f, 0.f };
			break;
		}

		Vec2 pos = position + dirVec * curSpeed * App::GetInstance()->deltaTime;

		int i = 0;
		auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");
		for (auto ob : obstacle)
		{
			auto spr = dynamic_pointer_cast<Sprite>(ob);
			if (Rect::CollisionPoint(spr->GetRect(), pos))
			{
				i++;
			}
		}

		if (i > 0)
		{
		}
		else
		{
			position = pos;
		}
	}

	head->position = position;
	shiled->position = position;

	hpBar->position = Vec2(position.x, position.y - 200.f);

	if(700 >= hp)
	{
		shiled->color.a -= App::GetInstance()->deltaTime;
	}
}

RECT Boss::GetRect()
{
	RECT r;
	r = Rect::Tex2SprTex(this);

	r.right -= 100.f;
	r.left += 100.f;
	r.bottom -= 100.f;
	r.top += 100.f;

	return r;
}

void Boss::Die()
{
	if(isDie) { return; }

	auto boom = ObjectList::GetInstance()->AddObject(new Boom(position), true, true);

	timers.push_back(Timer([&]()
	{
		SceneManager::GetInstance()->Change(new Outro());
	}, 8.f));
}
