#pragma once
class Outro : public Scene
{
public:
	Outro()
	{}
	virtual ~Outro()
	{}

public:
	shared_ptr<Animation> ani;
	shared_ptr<Sprite> fade;

public:
	virtual void Enter();
	virtual void Update();

	virtual void Exit()
	{
	}
};

