#include "DXUT.h"
#include"Precompile.h"
#include "Item.h"
#include"Player.h"
#include"GameManager.h"
#include"HealEffect.h"

void HpUpItem::Effect()
{
	auto get = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hp_Get/Hp_Get_0.png"), true, true);
	get->isNonCamera = true;
	get->position = App::GetInstance()->screenSize * 0.5f;

	auto ani = new Animation(get, 0.1f, false);
	for (size_t i = 0; i < 17; i++)
	{
		ani->AddFrame("Resources/Hp_Get/Hp_Get_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	auto ef = ObjectList::GetInstance()->AddObject(new HealEffect(), true ,true);
	ef->position = App::GetInstance()->screenSize * 0.5f;
	ef->isNonCamera = true;

	auto player = ObjectList::GetInstance()->GetObjects("Player");
	for (auto pyr : player)
	{
		auto spr = dynamic_pointer_cast<Player>(pyr);
		spr->hp += 30.f;
	}
	
	isRemoved = true;
}

void WeaponItem::Effect()
{
	auto get = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Weapon_Get/Weapon_Get_0.png"), true, true);
	get->isNonCamera = true;
	get->position = App::GetInstance()->screenSize * 0.5f;

	auto ani = new Animation(get, 0.1f, false);
	for(size_t i = 0; i < 17; i ++)
	{
		ani->AddFrame("Resources/Weapon_Get/Weapon_Get_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	auto player = ObjectList::GetInstance()->GetObjects("Player");
	for (auto pyr : player)
	{
		auto spr = dynamic_pointer_cast<Player>(pyr);
		if(spr->weapon == Player::WEAPON::RIFLE)
		{
			spr->weapon = Player::WEAPON::LAZER;
		}
		else
		{
			spr->weapon = Player::WEAPON::RIFLE;
		}
	}

	isRemoved = true;
}

void TimeItem::Effect()
{
	GameManager::GetInstance()->isStop = true;

	timers.push_back(Timer([&]()
	{
		GameManager::GetInstance()->isStop = false;
		isRemoved = true;
	}, 3.f));
}
