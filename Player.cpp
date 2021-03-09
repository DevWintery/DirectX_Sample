#include "DXUT.h"
#include"Precompile.h"
#include "Player.h"
#include"Bullet.h"
#include"Smoke.h"
#include"Zone.h"

void Player::Update()
{
	Sprite::Update();

	shadow->zOrder = zOrder - 1;
	shadow->position = Vec2(position.x, position.y + 40.f);

	_shadow->position = Vec2(position.x, position.y - 40.f);

	if(DXUTWasKeyPressed(VK_F9))
	{
		weapon = LAZER;
	}

	if (DXUTIsKeyDown('W') || DXUTIsKeyDown('A') || DXUTIsKeyDown('S') || DXUTIsKeyDown('D'))
	{
		if(state != DIE)
		{
			Move();
		}
	}
	else if(state != DIE)
	{
		state = IDLE;
	}

	if(state != RUN)
	{
		if(100.f > stamina)
		{
			stamina += 4 * App::GetInstance()->deltaTime;
		}
	}

	auto bullets = ObjectList::GetInstance()->GetObjects("EnemyBullet");
	for (auto bullet : bullets)
	{
		auto spr = dynamic_pointer_cast<Bullet>(bullet);
		if (Rect::CollisionPoint(spr->GetRect(), position) && state != DIE)
		{
			spr->Die();

			if (isStart || hitAni->count == hitAni->curIndex)
			{
				isStart = false;
				hitSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hit/Hit_1.png"), true, true);
				hitSpr->position = App::GetInstance()->screenSize * 0.5f + Vec2(rand() % 1000 - 500.f, rand() % 1000 - 500.f);
				hitSpr->isNonCamera = true;
				hitSpr->scale *= 1.5f;

				auto _ani = new Animation(hitSpr, 0.13f, false);
				for (size_t i = 1; i < 11; i++)
				{
					_ani->AddFrame("Resources/Hit/Hit_" + to_string(i) + ".png");
				}
				hitAni = AnimationManager::GetInstance()->AddAnimation(_ani);

				SceneManager::GetInstance()->curScene->camera->Shake();

				hp -= spr->damage;
			}
		}
	}

	auto zones = ObjectList::GetInstance()->GetObjects("Zone");
	for (auto zone : zones)
	{
		auto spr = dynamic_pointer_cast<Zone>(zone);
		if (Rect::CollisionPoint(spr->GetRect(), position))
		{
			spr->Active();
		}
	}

	auto trees = ObjectList::GetInstance()->GetObjects("Tree");
	for (auto tree : trees)
	{
		auto spr = dynamic_pointer_cast<Sprite>(tree);
		if (Rect::CollisionPoint(spr->GetRect(), position))
		{
			spr->color.a = 0.5f;
		}
		else
		{
			spr->color.a = 1.f;
		}
	}

	smokeTime += App::GetInstance()->deltaTime;
	if (smokeTime >= smokeRate && state == RUN)
	{
		CreateSmoke();
	}

	if(weapon == RIFLE)
	{
		attackRate = 0.3f;
	}

	if(weapon == LAZER)
	{
		attackRate = 0.1f;
	}

	attackTime += App::GetInstance()->deltaTime;
	if (DXUTIsKeyDown('J') && state != DIE && state != RUN)
	{
		Attack();
	}


	if(0 >= hp)
	{
		state = DIE;
	}

	AllStopAnimation();
	animations[weaponStr[weapon] + stateStr[state] + to_string(dir)]->isStop = false;
}

void Player::CreateSmoke()
{
	smokeTime = 0.f;
	auto smoke = ObjectList::GetInstance()->AddObject(new Smoke(), false);
	smoke->position = Vec2(position.x , position.y + 40.f);
	smoke->Init();
}

void Player::Attack()
{
	state = ATTACK;

	if (attackTime >= attackRate)
	{
		attackTime = 0.f;
		switch (weapon)
		{
		case Player::RIFLE:
			App::GetInstance()->PlayHochi();
			ObjectList::GetInstance()->AddObject(new NormalBullet(position, dir), true, true);
			break;
		case Player::LAZER:
			App::GetInstance()->PlayPew();
			ObjectList::GetInstance()->AddObject(new LazerBullet(position, dir), true, true);
			break;
		default:
			break;
		}
	}
}
