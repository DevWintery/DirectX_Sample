#include"DXUT.h"
#include"Precompile.h"
#include"Bullet.h"

Bullet::Bullet(const string & name, const Vec2 & d):
	Sprite(name), dir(d)
{
}

Bullet::~Bullet()
{
}

PlayerBullet::PlayerBullet(const string& name, const Vec2& d):
	Bullet(name, d)
{
	this->name = "PlayerBullet";
	this->scale = Vec2(0.5f, 0.5f);
	this->speed = 25.f;
}


void Bullet::Update()
{
	Sprite::Update();

	position += dir * speed;


	/*auto obstacle = ObjectList::GetInstance()->GetObjects("Obstacle");

	for (auto ob : obstacle)
	{
		auto tmp = dynamic_pointer_cast<Sprite>(ob);
		if (Rect::CollisionPoint(tmp->GetRect(), position))
		{
			Boom();
		}
	}*/
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{
	Bullet::Update();

	timers.push_back(Timer([&]() { isRemoved = true; }, 0.15f));
}

void PlayerBullet::Boom()
{
	auto spr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Bullet/bullet_1.png"));
	spr->position = position;
	spr->zOrder = zOrder;

	isVisible = false;

	auto ani = new Animation(spr, 0.05f, false);
	
	for(size_t i = 2; i < 7; i ++)
	{
		ani->AddFrame("Resources/Bullet/bullet_" + to_string(i) + ".png");
	}

	AnimationManager::GetInstance()->AddAnimation(ani);

	timers.push_back(Timer([&]()
	{
		spr->isRemoved = true;
		isRemoved = true;
	}, 1.f));
}

EnemyBullet::EnemyBullet(const string& name, const Vec2& d):
	Bullet(name, d)
{
	this->name = "EnemyBullet";
	this->scale = Vec2(0.5f, 0.5f);
	this->speed = 15.f;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	Bullet::Update();
}

void EnemyBullet::Boom()
{
	auto spr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Bullet/bullet_1.png"));
	spr->position = position;
	spr->zOrder = zOrder;

	isRemoved = true;

	auto ani = new Animation(spr, 0.05f, false);

	for (size_t i = 2; i < 7; i++)
	{
		ani->AddFrame("Resources/Bullet/bullet_" + to_string(i) + ".png");
	}

	AnimationManager::GetInstance()->AddAnimation(ani);
}
