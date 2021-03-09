#pragma once

class Main : public Scene
{
public:
	Main();
	virtual ~Main();

public:
	virtual void Enter() override;

	virtual void Update() override;

	virtual void Exit() override;

public:
	shared_ptr<Sprite> introducePopUp;
	shared_ptr<Sprite> helpPopUp;
	shared_ptr<Button> closeBtn;
};