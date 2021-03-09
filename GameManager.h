#pragma once

class GameManager : public Singleton<GameManager>
{
public:
	GameManager() :
		stage(1), isStop(false)
	{}
	virtual ~GameManager()
	{}

public:
	int stage;
	bool isStop;
};

