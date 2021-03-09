#include "DXUT.h"
#include"Precompile.h"
#include "Zone.h"
#include"Player.h"
#include"HealEffect.h"

void HealZone::Active()
{
	if (isActive) { return; }

	Zone::Active();

	auto ef = ObjectList::GetInstance()->AddObject(new HealEffect(), true, true);
	ef->position = App::GetInstance()->screenSize * 0.5f;
	ef->isNonCamera = true;

	auto pyr = ObjectList::GetInstance()->GetObjects("Player");
	for (auto p : pyr)
	{
		auto spr = dynamic_pointer_cast<Player>(p);
		spr->hp = 100.f;
	}
}

void WeaponZone::Active()
{
	if (isActive) { return; }

	Zone::Active();

	auto pyr = ObjectList::GetInstance()->GetObjects("Player");
	for (auto p : pyr)
	{
		auto spr = dynamic_pointer_cast<Player>(p);

		if (spr->weapon == Player::LAZER)
		{
			spr->weapon = Player::RIFLE;
		}
		else if (spr->weapon == Player::RIFLE)
		{
			spr->weapon = Player::LAZER;
		}
	}
}

