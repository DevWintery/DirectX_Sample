#pragma once

class Intro : public Scene
{
public:
	Intro();
	virtual ~Intro();

public:
	shared_ptr<Animation> ani;
	shared_ptr<Sprite> fade;

public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};

