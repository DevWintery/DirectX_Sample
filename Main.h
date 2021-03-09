#pragma once

class Main : public Scene
{
public:
	Main():
		speed(0.1f)
	{}
	virtual ~Main()
	{}

public:
	float speed;
	shared_ptr<Button> gameBtn;
	shared_ptr<Button> introBtn;
	shared_ptr<Button> helpBtn;
	shared_ptr<Button> returnBtn;
	shared_ptr<Button> quitBtn;

	shared_ptr<Sprite> titleSpr;
	shared_ptr<Animation> titleAni;

	shared_ptr<Sprite> introSpr;
	shared_ptr<Sprite> waySpr;

	shared_ptr<Sprite> cursor;

public:
	virtual void Enter();

	virtual void Update();

	virtual void Exit()
	{
	}
};

