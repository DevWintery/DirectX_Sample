#pragma once

class Player;
class Enemy;

class Game : public Scene
{
public:
	enum PHASE
	{
		LOADING_1,
		LOADING_2,
		LOADING_3,
		LOADING_4,
		PLAYING,
	};
public:
	Game():
		phase(LOADING_1)
	{
		isWin = false;
		isLose = false;
		time = 300;
		timeTime = 0.f;
	}
	virtual ~Game()
	{}

public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();

	bool isWin;
	bool isLose;

public:
	void LoadingScene();
	void Load();
	void EnemyLoad();
	void Win();
	void Lose();
	Vec2 RealPosition(const Vec2& pos);
	void CreateObstacle(const string& name, const Vec2& pos, bool visible = false);
	void CreateEnemy(int id, const Vec2& position);
	void SetTime();

public:
	shared_ptr<Player> player;
	shared_ptr<Sprite> loading;
	PHASE phase;
	vector<shared_ptr<Enemy>> enemys;
	shared_ptr<Sprite> resultPopUp;
	shared_ptr<ProgressBar> hpBar;
	shared_ptr<ProgressBar> staminaBar;

	shared_ptr<Sprite> weaponSpr;

	shared_ptr<Font> hpFont;
	shared_ptr<Font> timeFont;

	shared_ptr<Sprite> hpLow;

	shared_ptr<Sprite> shiftSpr;
	shared_ptr<Sprite> jSpr;

	shared_ptr<Sprite> stopEffect;

	shared_ptr<ProgressBar> loadingBar;

	vector<shared_ptr<Sprite>> arrows;

	int time;

	float timeTime;
};

