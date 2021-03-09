#pragma once

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

	bool start;
	int stage;
	bool result;
	int score;
	bool timeStop;
};