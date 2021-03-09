#include"DXUT.h"
#include"Precompile.h"
#include"Item.h"
#include"Player.h"
#include"GameManager.h"

Item::Item(const string & name):
	Sprite(name)
{
	this->name = "Item";
	scale *= 0.5f;
}

Item::~Item()
{
}

void Item::Effect(Player* player)
{
}

HpUpItem::HpUpItem():
	Item("Resources/Item/Item_Hp_0000")
{
}

HpUpItem::~HpUpItem()
{
}

void HpUpItem::Init()
{
	auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
	auto ani = new Animation(spr, 0.1f, true);

	for(size_t i = 0; i < 10; i ++)
	{
		ani->AddFrame("Resources/Item/Item_Hp_000" + to_string(i) + ".png");
	}

	animation = AnimationManager::GetInstance()->AddAnimation(ani);
}

void HpUpItem::Effect(Player* player)
{
	player->hp += 50.f;
}

TimeItem::TimeItem():
	Item("Resources/Item/Item_Time_0000.png")
{
}

TimeItem::~TimeItem()
{
}

void TimeItem::Init()
{
	auto spr = dynamic_pointer_cast<Sprite>(shared_from_this());
	auto ani = new Animation(spr, 0.1f, true);

	for (size_t i = 0; i < 10; i++)
	{
		ani->AddFrame("Resources/Item/Item_Time_000" + to_string(i) + ".png");
	}

	animation = AnimationManager::GetInstance()->AddAnimation(ani);
}

void TimeItem::Effect(Player * player)
{
	GameManager::GetInstance()->timeStop = true;

	player->timers.push_back(Timer([&](){ GameManager::GetInstance()->timeStop = false; }, 3.f));
}
