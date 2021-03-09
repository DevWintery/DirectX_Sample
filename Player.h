#pragma once

class Player : public Sprite
{
public:
	enum STATE
	{
		ATTACK1,
		DIE,
		IDLE,
		RUN,
		WALK,
		HIT,
		SIZE,
	};

public:
	Player();
	virtual ~Player();

public:

	float speed;
	int index;
	Vec2 dirV;
	STATE state;
	bool isUpdate;
	bool hit;
	bool hitting;
	float bulletRate;
	float bulletTime;
	bool isDie;
	float hp;
	float stamina;
	bool donMove;

	float maxHP;
	float maxStamina;

	bool isStart;

	float moveTime;
	float moveRate;

	shared_ptr<Animation> lowHpAni;
	shared_ptr<Sprite> lowHpSpr;
	shared_ptr<Animation> hitAni;
	shared_ptr<Sprite> hitSpr;
	shared_ptr<Sprite> under;
	Animation* animations[STATE::SIZE][8];
	string states[STATE::SIZE];

	void Init();
	void CheckState();
	void CheckAttack();
	void CheckMove();
	void CheckItem();
	Vec2 GetCursorDir();
	void CheckHit();

	void Die() { state = DIE; }

public:
	virtual void Update() override;

	void AllAnimationStop()
	{
		for(size_t type = 0; type < STATE::SIZE; type ++)
		{
			for(size_t i = 0; i < 8; i ++)
			{
				animations[type][i]->isStop = true;
			}
		}
	}
};