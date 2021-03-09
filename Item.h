#pragma once

class Player;
class Item : public Sprite
{
public:
	Item(const string& name);
	virtual ~Item();

public:
	virtual void Init() {}
	virtual void Effect(Player* player);

public:
	shared_ptr<Animation> animation;
};

class HpUpItem : public Item
{
public:
	HpUpItem();
	virtual ~HpUpItem();

	virtual void Init() override;

public:
	virtual void Effect(Player* player) override;
};

class TimeItem : public Item
{
public:
	TimeItem();
	virtual ~TimeItem();

public:
	virtual void Init() override;
	virtual void Effect(Player* player) override;
};