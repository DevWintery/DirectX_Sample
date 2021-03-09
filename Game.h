#pragma once

class Player;
class Enemy;

class Game : public Scene
{
public:
	enum PHASE
	{
		NONE,
		LOADING,
		LOADING_2,
		LOADING_3,
		LOADING_4,
		LOADING_5,
		LOADING_6,
		LOADING_7,
		PLAYING,
	};

public:
	Game();
	virtual ~Game();

public:
	virtual void Enter() override;

	virtual void Update() override;

	virtual void Exit() override;

public:
	void CreateLoading();
	void CreatePlayer();
	void CreateUI();
	void CreateMap();
	void CreateEnemy();
	void CheckTime();
	void CheckEnemy();

	void CreateSprite(const string& name, const Vec2& pos, float rotation = 0.f, int zOrder = 0);
	void CreateHouse(const string& name, const Vec2& pos, float rotation = 0.f, int zOrder = 0);
	void CreateObstacle(const Vec2& position, const Vec2& scale, float rotation);

public:
	bool isLoading;
	
	shared_ptr<Sprite> loadingSpr;
	shared_ptr<Sprite> startSpr;
	shared_ptr<Animation> startAni;
	shared_ptr<ProgressBar> hpBar;
	shared_ptr<ProgressBar> staminaBar;
	shared_ptr<Sprite> attackBtn;
	shared_ptr<Sprite> runBtn;
	shared_ptr<Sprite> gunSpr;
	shared_ptr<Sprite> resultSpr;
	shared_ptr<Animation> resultAni;
	shared_ptr<Player> player;
	vector<shared_ptr<Enemy>> enemys;
	shared_ptr<Font> count;
	shared_ptr<Sprite> policeHouse;
	shared_ptr<Sprite> timeSpr;
	shared_ptr<Font> hpText;

	float time;
	int clock;
	bool result;

	PHASE phase;
};