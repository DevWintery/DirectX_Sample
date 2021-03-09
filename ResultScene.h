#pragma once

class ResultScene : public Scene
{
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};