#pragma once

class Enemy : public Sprite
{
public:
	enum STATE
	{
		NONE,
		DETECT,
		SIZE
	};

public:
	Enemy();
	Enemy(const string& name);
	virtual ~Enemy();

	virtual void Init() {}
	virtual void Update() override;
	virtual void Die();

	virtual void Detected() { state = DETECT; }
	virtual void None() { state = NONE; }

public:
	STATE state;
	float hp;
	Vec2 dir;
};

class Robot_1 : public Enemy
{
public:
	Robot_1();
	virtual ~Robot_1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Die() override;

	void Patrol();
	void Track();

public:
	Animation* animations[8];
	bool detecting;
};

class Robot_2 : public Enemy
{
public:
	Robot_2();
	virtual ~Robot_2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Die() override;

	void Patrol();
	void Track();

public:
	bool detecting;
	float bulletTime;
	float bulletRate;
	Animation* animations[STATE::SIZE][8];
};

class ControlUnit : public Enemy
{
public:
	ControlUnit();
	virtual ~ControlUnit();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Die() override;

	void Patrol();
	void Shot();

public:
	shared_ptr<Sprite> robot_b;
	shared_ptr<Sprite> robot_h;

	Vec2 hDir;
	Vec2 bDir;
	bool detecting;
	bool isRush;
	bool isDie;
	float bulletTime;
	float bulletRate;

	float dieTime;
	float dieRate;
};