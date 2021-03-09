#include"DXUT.h"
#include"Precompile.h"
#include"Player.h"
#include"Bullet.h"
#include"Main.h"
#include"Item.h"
#include"GameManager.h"

Player::Player():
	Sprite("Resources/CT_M/Ct_M_1_0000.png"), speed(2.f), states{ "Attack1", "Die", "Idle", "Run", "Walk", "WalkHit"}, isUpdate(false), hit(false), hitting(false), bulletRate(0.15f), bulletTime(0.f), hp(100.f), maxHP(100.f), stamina(100.f), maxStamina(100.f), isDie(false), donMove(false), moveRate(0.2f), moveTime(0.f)
{
	this->name = "Player";
}

Player::~Player()
{
}

void Player::Init()
{
	isStart = true;

	lowHpSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/LowHealth/LowHealth_000.png"));
	lowHpSpr->position = App::GetInstance()->screenSize * 0.5f;
	lowHpSpr->isVisible = false;
	lowHpSpr->isNonCamera = true;

	auto ani = new Animation(lowHpSpr, 0.1f, true);
	for(size_t i = 0; i < 6; i ++)
	{
		ani->AddFrame("Resources/LowHealth/LowHealth_00" + to_string(i) + ".png");
	}
	lowHpAni = AnimationManager::GetInstance()->AddAnimation(ani);

	under = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Player_Under_3.png"));
	under->parent = this;

	under->zOrder = zOrder - 1;
	for (size_t type = 0; type < STATE::SIZE; type++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
			auto ani = animations[type][i] = new Animation(spr, 0.1f, true);
			ani->isStop = true;

			if(type == STATE::RUN)
			{
				ani->freamRate = 0.05f;
			}
			if(type == STATE::ATTACK1)
			{
				ani->freamRate = 0.07f;
			}
			AnimationManager::GetInstance()->AddAnimation(ani);
		}
	}

	for(size_t i = 0; i < 8; i ++)
	{
		animations[STATE::DIE][i]->isLoop = false;
	}


	for(size_t type = 0; type < STATE::SIZE; type ++)
	{

		for (size_t i = 1; i < 6; i++)
		{
			string offset = "Resources/Render/";
			offset += to_string(i) + "/Ct_M_";
			offset += states[type];
			offset += "_";
			switch (type)
			{
			case STATE::RUN:
				for (size_t run = 0; run < 10; run++)
				{
					string path = to_string((i * 10000) + run);
					path += ".png";

					animations[type][i - 1]->AddFrame(offset + path);
				}
				break;

			case STATE::HIT:
				break;
			case STATE::WALK:
				for (size_t walk = 30; walk < 40; walk++)
				{
					string path = to_string((i * 10000) + walk);
					path += ".png";

					animations[type][i - 1]->AddFrame(offset + path);
				}
				break;

			case STATE::IDLE:
				for (size_t idle = 45; idle < 65; idle++)
				{
					string path = to_string((i * 10000) + idle);
					path += ".png";

					animations[type][i - 1]->AddFrame(offset + path);

				}
				break;

			case STATE::ATTACK1:
				for (size_t attack = 70; attack < 90; attack++)
				{
					string path = to_string((i * 10000) + attack);
					path += ".png";

					animations[type][i - 1]->AddFrame(offset + path);
				}
				break;

			case STATE::DIE:
				for (size_t die = 95; die < 106; die++)
				{
					string path = to_string((i * 10000) + die);
					path += ".png";

					animations[type][i - 1]->AddFrame(offset + path);
				}
				break;
			}
		}
	}


	isUpdate = true;
}

void Player::CheckState()
{
	switch (state)
	{
	case Player::DIE:
		AllAnimationStop();
		animations[STATE::DIE][index - 1]->isStop = false;
		break;
	case Player::IDLE:
		AllAnimationStop();
		animations[STATE::IDLE][index - 1]->isStop = false;
		break;
	case Player::RUN:
		AllAnimationStop();
		animations[STATE::RUN][index - 1]->isStop = false;
		break;
	case Player::WALK:
		AllAnimationStop();
		animations[STATE::WALK][index - 1]->isStop = false;
		break;
	case Player::ATTACK1:
		AllAnimationStop();
		animations[STATE::ATTACK1][index - 1]->isStop = false;
		break;
	case Player::HIT:
		break;
	case Player::SIZE:
		break;
	default:
		break;
	}
}

void Player::CheckAttack()
{
	Vec2 dir = GetCursorDir();

	bulletTime += App::GetInstance()->deltaTime;
	
	if(!DXUTIsKeyDown(VK_SHIFT) && App::GetInstance()->leftDown)
	{
		if(state != DIE)
		{
			state = STATE::ATTACK1;
		}

		if(bulletTime >= bulletRate)
		{
			bulletTime = 0.f;
			auto tmp = ObjectList::GetInstance()->AddObject(new PlayerBullet("Resources/Bullet/bullet_1.png", dir));
			tmp->position = position;
			tmp->zOrder = 6;
		}
	}
}

void Player::CheckMove()
{
	Vec2 pos = position;
	float runSpeed = speed * 1.5f;
	if (DXUTIsKeyDown('W'))
	{
		if (DXUTIsKeyDown(VK_SHIFT))
		{
			pos.y -= runSpeed;
		}
		else
		{
			pos.y -= speed;
		}
	}

	if (DXUTIsKeyDown('S'))
	{
		if (DXUTIsKeyDown(VK_SHIFT))
		{
			pos.y += runSpeed;
		}
		else
		{
			pos.y += speed;
		}
	}

	if (DXUTIsKeyDown('A'))
	{
		if (DXUTIsKeyDown(VK_SHIFT))
		{
			pos.x -= runSpeed;
		}
		else
		{
			pos.x -= speed;
		}
	}
	if (DXUTIsKeyDown('D'))
	{
		if (DXUTIsKeyDown(VK_SHIFT))
		{
			pos.x += runSpeed;
		}
		else
		{
			pos.x += speed;
		}
	}
	else
	{
		if(state != DIE)
		{
			state = STATE::IDLE;
			stamina += 5 * App::GetInstance()->deltaTime;
		}
	}
	if (DXUTIsKeyDown('W') || DXUTIsKeyDown('A') || DXUTIsKeyDown('S') || DXUTIsKeyDown('D'))
	{
		moveTime += App::GetInstance()->deltaTime;
		if(moveTime >= moveRate)
		{
			moveTime = 0.f;
			auto moveEf = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Effect_1/Move_1.png"));
			moveEf->position = position + Vec2(0.f, 10.f);
			moveEf->zOrder = zOrder - 1;

			auto moveAni = new Animation(moveEf, 0.1f, false);
			for (size_t i = 1; i < 6; i++)
			{
				moveAni->AddFrame("Resources/Effect_1/Move_" + to_string(i) + ".png");
			}
			AnimationManager::GetInstance()->AddAnimation(moveAni);
		}

		if (DXUTIsKeyDown(VK_SHIFT) && stamina >= 0.f)
		{
			if (state != DIE)
			{
				state = STATE::RUN;
				stamina -= 10 * App::GetInstance()->deltaTime;
			}
		}

		else
		{
			if (state != DIE)
			{
				state = STATE::WALK;
				stamina += 5 * App::GetInstance()->deltaTime;
			}
		}
	}

	Vec2 _pos = pos;
	_pos.y -= 50.f;
	OBB2D tmpOBB(_pos);
	tmpOBB.moveTo(_pos);

	int i = 0;
	auto tmps = ObjectList::GetInstance()->GetObjects("Obstacle");
	for (auto tmp : tmps)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if(tmpOBB.overlaps(t->obb))
		{
			i++;
		}
	}

	if(i > 0)
	{
		i = 0;
	}
	else
	{
		position = pos;
	}

	auto police = ObjectList::GetInstance()->GetObjects("Police");
	for (auto tmp : police)
	{
		auto t = dynamic_pointer_cast<Sprite>(tmp);

		if (tmpOBB.overlaps(t->obb))
		{
		}
	}
}

void Player::CheckItem()
{
	auto items = ObjectList::GetInstance()->GetObjects("Item");
	for(auto item : items)
	{
		auto i = dynamic_pointer_cast<Item>(item);
		if(Rect::CollisionPoint(i->GetRect(), position))
		{
			i->Effect(this);
			i->isRemoved = true;
		}
	}
}

Vec2 Player::GetCursorDir()
{
	D3DVIEWPORT9 viewport;
	DXUTGetD3D9Device()->GetViewport(&viewport);

	shared_ptr<Camera> camera = SceneManager::GetInstance()->curScene->camera;

	Matrix4 identity;
	D3DXMatrixIdentity(&identity);

	Vec3 mousePosition(App::GetInstance()->mousePosition.x, App::GetInstance()->mousePosition.y, 0);
	D3DXVec3Unproject(&mousePosition, &mousePosition, &viewport, &camera->orthographicMatrix, &camera->viewMatrix, &identity);

	auto dirVec = (Vec2&)mousePosition - position;
	Vec2 dir;
	D3DXVec2Normalize(&dir, &dirVec);

	return dir;
}

void Player::CheckHit()
{
	auto bullets = ObjectList::GetInstance()->GetObjects("EnemyBullet");

	for(size_t i = 0; i < bullets.size(); i ++)
	{
		auto b = dynamic_pointer_cast<Bullet>(bullets[i]);
		if(Rect::CollisionPoint(b->GetRect(), position))
		{
			b->Boom();

			if(isStart || hitAni->count == hitAni->curIndex)
			{
				isStart = false;

				hitSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hit/Hit_1.png"));
				hitSpr->position = App::GetInstance()->screenSize * 0.5f + Vec2(rand() % 1000 - 500.f, rand() % 1000 - 500.f);
				hitSpr->scale *= 1.3f;
				hitSpr->isNonCamera = true;
				hitSpr->zOrder = 99;

				auto _ani = new Animation(hitSpr, 0.13f, false);
				for (size_t i = 1; i < 11; i++)
				{
					_ani->AddFrame("Resources/Hit/Hit_" + to_string(i) + ".png");
				}
				hitAni = AnimationManager::GetInstance()->AddAnimation(_ani);

				SceneManager::GetInstance()->curScene->camera->Shake();

				hp -= 10.f;
			}
		}
	}

	if(0 >= hp && !isDie)
	{
		state = DIE;
		isDie = true;

		timers.push_back(Timer([&]()
		{
			SceneManager::GetInstance()->Change(new Main());
		}, 3.f));
	}
}

void Player::Update()
{
	if(!isUpdate) { return; }
	if(GameManager::GetInstance()->result) { return; }

	Sprite::Update();

	if(state == DIE) { return; }

	auto twoPI = 2 * D3DX_PI;

	auto dirVec = GetCursorDir();
	float dir = atan2(dirVec.y, dirVec.x);
	dir += twoPI;

	int _index = static_cast<int>(fmod(dir, twoPI) / twoPI * 8 + 1.5f);
	index = _index = (_index + 1) % 8 + 1;

	if (hit)
	{
		hit = false;
		hitting = true;
		timers.push_back(Timer([&]() { hitting = false; }, 0.45f));
	}

	switch (_index)
	{
	case 2:
		scale.x = 0.5f;
		break;
	case 3:
		scale.x = 0.5f;
		break;
	case 4:
		scale.x = 0.5f;
		break;
	case 6:
		index = 4;
		scale.x = -0.5f;
		break;
	case 7:
		index = 3;
		scale.x = -0.5f;
		break;
	case 8:
		index = 2;
		scale.x = -0.5f;
		break;
	default:
		break;
	}

	CheckMove();

	if(hp >= maxHP)
	{
		hp = maxHP;
	}

	if(stamina >= maxStamina)
	{
		stamina = maxStamina;
	}

	if (hitting)
	{
		state = STATE::HIT;
		speed = 1.f;
	}
	else
	{
		speed = 2.f;
	}

	if(DXUTWasKeyPressed(VK_SPACE))
	{
		hp -= 10.f;
	}

	CheckAttack();
	CheckHit();

	if(30.f > hp)
	{
		lowHpSpr->isVisible = true;
	}
	else
	{
		lowHpSpr->isVisible = false;
	}

	CheckItem();
	CheckState();
}
