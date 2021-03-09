#pragma once

class Intro : public Scene
{
public:
	Intro();
	virtual ~Intro();

public:
	virtual void Enter() override;

	virtual void Update() override;

	virtual void Exit() override;

public:
	shared_ptr<Animation> introAni;

	float rate;
	float time;
};