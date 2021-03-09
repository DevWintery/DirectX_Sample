#pragma once

class Bullet : public Sprite
{
public:
	Bullet(const string& name, const Vec2& d);
	virtual ~Bullet();

	Vec2 dir;
	float speed;

public:
	virtual void Update() override;
	virtual void Boom() {};
};

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(const string& name, const Vec2& d);
	virtual ~PlayerBullet();

public:
	virtual void Update() override;
	virtual void Boom() override;

public:
	shared_ptr<Animation> dieAni;
};

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(const string& name, const Vec2& d);
	virtual ~EnemyBullet();

public:
	virtual void Update() override;
	virtual void Boom() override;
};