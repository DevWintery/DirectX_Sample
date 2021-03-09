#include"DXUT.h"
#include"Precompile.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Item.h"
#include"GameManager.h"

Enemy::Enemy() :
	Sprite(), hp(500.f), dir(static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1))
{
	this->name = "Enemy";
}

Enemy::Enemy(const string& name):
	Sprite(name), hp(500.f), dir(static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1))
{
	this->name = "Enemy";
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Sprite::Update();

	auto tmp = ObjectList::GetInstance()->GetObjects("PlayerBullet");
	for(size_t i = 0; i < tmp.size(); i ++)
	{
		auto t = dynamic_pointer_cast<Bullet>(tmp[i]);

		if(Rect::CollisionPoint(t->GetRect(), position))
		{
			t->Boom();
			hp -= 20.f;
		}
	}

	if(0 >= hp)
	{
		Die();
	}
}

void Enemy::Die()
{

}

Robot_1::Robot_1():
	Enemy("Resources/Monster/Mob_1/1/Enemy_2_1_1.png"), detecting(false)
{
}

Robot_1::~Robot_1()
{
}

void Robot_1::Init()
{
	for (size_t i = 0; i < 8; i++)
	{
		auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
		auto ani = animations[i] = new Animation(spr, 0.1f, true);
		ani->isStop = true;
	}

	for (size_t i = 1; i < 9; i++)
	{
		string offset = "Resources/Monster/Mob_1/";
		offset += to_string(i);
		offset += "/Enemy_2_";
		offset += to_string(i);

		for(size_t j = 1; j < 3; j ++)
		{
			animations[i - 1]->AddFrame(offset + "_" + to_string(j) + ".png");
		}

		AnimationManager::GetInstance()->AddAnimation(animations[i - 1]);
	}
}

void Robot_1::Update()
{
	Enemy::Update();

	if(GameManager::GetInstance()->timeStop || !GameManager::GetInstance()->start) { return; }

	switch (state)
	{
	case NONE:
		Patrol();
		break;
	case DETECT:
		Track();
		break;
	default:
		break;
	}
}

void Robot_1::Die()
{
	auto t = ObjectList::GetInstance()->AddObject(new HpUpItem());
	t->Init();
	t->position = position;

	isRemoved = true;
}

void Robot_1::Patrol()
{
	auto twoPI = 2 * D3DX_PI;
	
	if(!detecting)
	{
		detecting = true;
		timers.push_back(Timer([&]()
		{
			dir = { static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1) };
			detecting = false;
		}, 3.f));
	}

	auto dirVec = dir;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	for(size_t i = 0; i < 8; i ++)
	{
		animations[i]->isStop = true;
	}

	animations[_index - 1]->isStop = false;

	Vec2 pos = position + dir;
	
	OBB2D tmpOBB(pos);
	tmpOBB.moveTo(pos);

	int i = 0;
	auto tmps = ObjectList::GetInstance()->GetObjects("Obstacle");
	for (auto tmp : tmps)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if (tmpOBB.overlaps(t->obb))
		{
			i++;
		}
	}

	if (i > 0)
	{
		i = 0;
	}
	else
	{
		position = pos;
	}
}

void Robot_1::Track()
{
	auto twoPI = 2 * D3DX_PI;

	auto player = ObjectList::GetInstance()->GetObjects("Player")[0];

	auto dirVec = player->position - position;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	for (size_t i = 0; i < 8; i++)
	{
		animations[i]->isStop = true;
	}

	animations[_index - 1]->isStop = false;

	Vec2 pos;

	Vec2 dir;
	D3DXVec2Normalize(&dir, &dirVec);
	pos += dir;

	pos = position + dir;

	OBB2D tmpOBB(pos);
	tmpOBB.moveTo(pos);

	int i = 0;
	auto tmps = ObjectList::GetInstance()->GetObjects("Obstacle");
	for (auto tmp : tmps)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if (tmpOBB.overlaps(t->obb))
		{
			i++;
		}
	}

	if (i > 0)
	{
		i = 0;
	}
	else
	{
		position = pos;
	}
}

Robot_2::Robot_2():
	Enemy("Resources/Monster/Mob_2/1/Enemy_3_1_1.png"), detecting(false), bulletRate(0.7f), bulletTime(0.f)
{
}

Robot_2::~Robot_2()
{
}

void Robot_2::Init()
{
	for(size_t type = 0; type < STATE::SIZE; type ++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
			auto ani = animations[type][i] = new Animation(spr, 0.1f, true);
			ani->isStop = true;

			AnimationManager::GetInstance()->AddAnimation(ani);
		}
	}

	for(size_t type = 0; type < STATE::SIZE; type ++)
	{
		for (size_t i = 1; i < 9; i++)
		{
			string offset = "Resources/Monster/Mob_2/";
			offset += to_string(i);
			offset += "/Enemy_3_";

			switch (type)
			{
			case STATE::NONE:
				for(size_t none = 1; none < 9; none ++)
				{
					animations[type][i - 1]->AddFrame(offset + to_string(i) + "_" + to_string(none) + ".png");
				}
				break;

			case STATE::DETECT:
				for (size_t detect = 1; detect < 9; detect++)
				{
					animations[type][i - 1]->AddFrame(offset + "Attack1_" + to_string(i) + "_" + to_string(detect) + ".png");
				}
				break;
			}
		}
	}
}

void Robot_2::Update()
{
	Enemy::Update();

	if (GameManager::GetInstance()->timeStop || !GameManager::GetInstance()->start) { return; }

	switch (state)
	{
	case NONE:
		Patrol();
		break;
	case DETECT:
		Track();
		break;
	default:
		break;
	}
}

void Robot_2::Die()
{
	auto t = ObjectList::GetInstance()->AddObject(new TimeItem());
	t->Init();
	t->position = position;

	isRemoved = true;
}

void Robot_2::Patrol()
{
	auto twoPI = 2 * D3DX_PI;

	if (!detecting)
	{
		detecting = true;
		timers.push_back(Timer([&]()
		{
			dir = { static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1) };
			detecting = false;
		}, 3.f));
	}

	auto dirVec = dir;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	for(size_t type = 0; type < STATE::SIZE; type ++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			animations[type][i]->isStop = true;
		}
	}
	animations[STATE::NONE][_index - 1]->isStop = false;

	Vec2 pos = position + dir;

	OBB2D tmpOBB(pos);
	tmpOBB.moveTo(pos);

	int i = 0;
	auto tmps = ObjectList::GetInstance()->GetObjects("Obstacle");
	for (auto tmp : tmps)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if (tmpOBB.overlaps(t->obb))
		{
			i++;
		}
	}

	if (i > 0)
	{
		i = 0;
	}
	else
	{
		position = pos;
	}
}

void Robot_2::Track()
{
	auto twoPI = 2 * D3DX_PI;

	auto player = ObjectList::GetInstance()->GetObjects("Player")[0];

	auto dirVec = player->position - position;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	for (size_t type = 0; type < STATE::SIZE; type++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			animations[type][i]->isStop = true;
		}
	}
	animations[STATE::DETECT][_index - 1]->isStop = false;

	Vec2 output;
	D3DXVec2Normalize(&output, &dirVec);

	bulletTime += App::GetInstance()->deltaTime;

	if (bulletTime >= bulletRate)
	{
		bulletTime = 0.f;
		auto tmp = ObjectList::GetInstance()->AddObject(new EnemyBullet("Resources/Bullet/bullet_1.png", output));
		tmp->position = position;
		tmp->zOrder = 6;
	}
}

ControlUnit::ControlUnit():
	Enemy(), detecting(false), isRush(false), bDir(0.f, 0.f), bulletRate(0.05f), bulletTime(0.f), isDie(false), dieRate(0.3f), dieTime(0.f)
{
	hp = 1000.f;

	robot_b = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Enemy/1/Enemy1_B_1.png"));
	robot_b->parent = this;

	robot_h = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Enemy/1/Enemy1_H_1.png"));
	robot_h->parent = this;;
}

ControlUnit::~ControlUnit()
{
}

void ControlUnit::Init()
{
}

void ControlUnit::Update()
{
	Enemy::Update();

	if (isDie)
	{
		dieTime += App::GetInstance()->deltaTime;

		if (dieTime >= dieRate)
		{
			dieTime = 0.f;
			auto tmp = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Boss_Boom/Boss_Boom_1.png"));
			tmp->position = position + Vec2(rand() % 100 - 50, rand() % 100 - 50);
			tmp->zOrder = zOrder + 1;

			auto ani = new Animation(tmp, 0.1f, false);
			for (size_t i = 1; i < 9; i++)
			{
				ani->AddFrame("Resources/Boss_Boom/Boss_Boom_" + to_string(i) + ".png");
			}
			AnimationManager::GetInstance()->AddAnimation(ani);
		}
	}

	if (GameManager::GetInstance()->timeStop || !GameManager::GetInstance()->start || isDie) { return; }

	switch (state)
	{
	case NONE:
		Patrol();
		break;
	case DETECT:
		Shot();
		break;
	default:
		break;
	}
}

void ControlUnit::Die()
{
	timers.push_back(Timer([&](){
		GameManager::GetInstance()->result = true;}, 3.f));

	isDie = true;
	//robot_b->isRemoved = true;
	//robot_h->isRemoved = true;

	//isRemoved = true;
}

void ControlUnit::Patrol()
{
	auto twoPI = 2 * D3DX_PI;

	if (!detecting)
	{
		detecting = true;
		robot_b->timers.push_back(Timer([&]()
		{
			bDir = { static_cast<float>((rand() % 3) - 1), static_cast<float>((rand() % 3) - 1) };
			detecting = false;
		}, 5.f));
	}

	auto dirVec = bDir;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	robot_b->texture = TextureManager::GetInstance()->LoadTexture("Resources/Enemy/" + to_string(_index) + "/Enemy1_B_" + to_string(_index) + ".png");

	Vec2 pos = position + bDir;

	OBB2D tmpOBB(pos);
	tmpOBB.moveTo(pos);

	int i = 0;
	auto tmps = ObjectList::GetInstance()->GetObjects("Obstacle");
	for (auto tmp : tmps)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if (tmpOBB.overlaps(t->obb))
		{
			i++;
		}
	}

	if (i > 0)
	{
		i = 0;
	}
	else
	{
		position = pos;
	}
}

void ControlUnit::Shot()
{
	auto twoPI = 2 * D3DX_PI;

	hDir = ObjectList::GetInstance()->GetObjects("Player")[0]->position - position;
	auto dirVec = hDir;
	float _dir = atan2(dirVec.y, dirVec.x);
	_dir += twoPI;

	int _index = static_cast<int>(fmod(_dir, twoPI) / twoPI * 8 + 1.5f);
	_index = (_index + 1) % 8 + 1;

	robot_h->texture = TextureManager::GetInstance()->LoadTexture("Resources/Enemy/" + to_string(_index) + "/Enemy1_H_" + to_string(_index) + ".png");

	bulletTime += App::GetInstance()->deltaTime;
	if (bulletTime >= bulletRate)
	{
		bulletTime = 0.f;
		Vec2 out;
		D3DXVec2Normalize(&out, &hDir);
		out = Math::RotateVector2(out, rand() % 40 - 20);
		auto tmp = ObjectList::GetInstance()->AddObject(new EnemyBullet("Resources/Boss_bullet.png", out));
		tmp->position = position;
	}
}
