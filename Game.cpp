#include"DXUT.h"
#include"Precompile.h"
#include"Game.h"
#include"Player.h"
#include"Enemy.h"
#include"GameManager.h"
#include"ResultScene.h"
#include"Main.h"

Game::Game():
	phase(NONE), time(0), clock(300)
{
}

Game::~Game()
{
}

void Game::Enter()
{
	Scene::Enter();

	GameManager::GetInstance()->result = false;
	GameManager::GetInstance()->score = 0;
	GameManager::GetInstance()->start = false;
}

void Game::Update()
{
	if(GameManager::GetInstance()->result)
	{
		resultSpr->isVisible = true;
		resultAni->isStop = false;

		if((resultAni->curIndex == resultAni->count) && DXUTWasKeyPressed('Y'))
		{
			int stage = GameManager::GetInstance()->stage++;
			if (stage == 2)
			{
				GameManager::GetInstance()->score += clock * 5.5f;
				SceneManager::GetInstance()->Change(new ResultScene());
			}
			else
			{
				SceneManager::GetInstance()->Change(new Game());
			}
		}
	}
	else
	{
		switch (phase)
		{
		case Game::NONE:
			CreateLoading();
			phase = LOADING;
			return;
		case Game::LOADING:
			CreateMap();
			
			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_2.png");

			phase = LOADING_2;

			return;

		case Game::LOADING_2:
			CreatePlayer();

			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_3.png");

			phase = LOADING_3;
			return;

		case Game::LOADING_3:
			CreateEnemy();

			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_4.png");

			phase = LOADING_4;
			return;

		case Game::LOADING_4:
			CreateUI();

			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_5.png");

			phase = LOADING_5;
			return;
			
		case Game::LOADING_5:
			timeSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Time_1.png"));
			timeSpr->position.x = App::GetInstance()->screenSize.x * 0.5f;
			timeSpr->position.y = timeSpr->texture->rect.bottom - 50.f;
			timeSpr->zOrder = 99;
			timeSpr->isNonCamera = true;

			count = ObjectList::GetInstance()->AddObject(new Font(100, L"Arial", L"5 : 00"));
			count->position.x = App::GetInstance()->screenSize.x * 0.5f - 90.f;
			count->position.y = 0.f;
			count->zOrder = 100;

			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_6.png");

			phase = LOADING_6;

			return;

		case Game::LOADING_6:
			resultSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Win/Win_1.png"));
			resultSpr->position = App::GetInstance()->screenSize * 0.5f;
			resultSpr->zOrder = 50;
			resultSpr->isVisible = false;
			resultSpr->isNonCamera = true;
			{
				auto ani = new Animation(resultSpr, 0.1f, false);
				for (size_t i = 1; i < 24; i++)
				{
					ani->AddFrame("Resources/Win/Win_" + to_string(i) + ".png");
				}
				ani->isStop = true;
				resultAni = AnimationManager::GetInstance()->AddAnimation(ani);
			}

				startSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Objective/Objective_" + to_string(GameManager::GetInstance()->stage) + "/Objective_1.png"));
				startSpr->position = App::GetInstance()->screenSize * 0.5f;
				startSpr->isNonCamera = true;
				startSpr->zOrder = 100;
				{
				auto sAni = new Animation(startSpr, 0.1f, false);
				for (size_t i = 1; i < 30; i++)
				{
					sAni->AddFrame("Resources/Objective/Objective_" + to_string(GameManager::GetInstance()->stage) + "/Objective_" + to_string(i) + ".png");
				}
				startAni = AnimationManager::GetInstance()->AddAnimation(sAni);
				}

			loadingSpr->texture = TextureManager::GetInstance()->LoadTexture("Resources/Loading/Loading_7.png");

			phase = LOADING_7;

			return;

		case Game::LOADING_7:

			ObjectList::GetInstance()->RemoveObject(loadingSpr);
			camera->scale *= 1.5f;

			phase = PLAYING;

			return;
		case Game::PLAYING:
			if(!(startAni->count == startAni->curIndex)) { GameManager::GetInstance()->start = false; }
			else { GameManager::GetInstance()->start = true; }

			hpBar->SetValue(player->hp / player->maxHP);
			staminaBar->SetValue(player->stamina / player->maxStamina);

			if(DXUTIsKeyDown(VK_SHIFT))
			{
				runBtn->texture = TextureManager::GetInstance()->LoadTexture("Resources/InGame_Ui/Run_Btn_2.png");
			}
			else
			{
				runBtn->texture = TextureManager::GetInstance()->LoadTexture("Resources/InGame_Ui/Run_Btn_1.png");
			}

			if (App::GetInstance()->leftDown)
			{
				attackBtn->texture = TextureManager::GetInstance()->LoadTexture("Resources/InGame_Ui/Attack_Btn_2.png");
			}
			else
			{
				attackBtn->texture = TextureManager::GetInstance()->LoadTexture("Resources/InGame_Ui/Attack_Btn_1.png");
			}
			break;
		default:
			break;
		}

		if(!camera->shaking)
		{
			camera->position = player->position;
		}

		CheckEnemy();
		CheckTime();

		hpText->text = to_wstring(static_cast<int>(player->hp)) + L"/100";

		if(0.f >= clock)
		{
			player->Die();

			if (!GameManager::GetInstance()->result)
			{
				GameManager::GetInstance()->result = true;
			}
		}
	}
}

void Game::Exit()
{
	Scene::Exit();
}

void Game::CreateLoading()
{
	loadingSpr = ObjectList::GetInstance()->AddObject(new Sprite("Loading/Loading_1.png"));
	loadingSpr->position = App::GetInstance()->screenSize * 0.5f; 
	loadingSpr->zOrder = 500;
}

void Game::CreatePlayer()
{
	player = ObjectList::GetInstance()->AddObject(new Player());
	player->position = App::GetInstance()->screenSize * 0.4f;
	player->scale *= 0.5f;
	player->zOrder = 5;
	player->Init();
}

void Game::CreateUI()
{
	auto _interface = ObjectList::GetInstance()->AddObject(new Sprite("Resources/InGame_Ui/Info_Btn_1.png"));
	_interface->position.y = App::GetInstance()->screenSize.y * 0.85f;
	_interface->position.x = App::GetInstance()->screenSize.x * 0.15f;
	_interface->isNonCamera = true;

	_interface->zOrder = 29;

	hpBar = ObjectList::GetInstance()->AddObject(new ProgressBar("Resources/InGame_Ui/Hp_Bar_1.png"));
	hpBar->position.x = App::GetInstance()->screenSize.x * 0.15f + 72.f;
	hpBar->position.y = App::GetInstance()->screenSize.y * 0.85f + 23.f;
	hpBar->zOrder = 30;

	staminaBar = ObjectList::GetInstance()->AddObject(new ProgressBar("Resources/InGame_Ui/Stamina_Bar_1.png"));
	staminaBar->position.x = App::GetInstance()->screenSize.x * 0.15f + 52.f;
	staminaBar->position.y = App::GetInstance()->screenSize.y * 0.85f + 86.f;
	staminaBar->zOrder = 30;

	gunSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/InGame_Ui/Weapone_Btn_1.png"));
	gunSpr->position = App::GetInstance()->screenSize * 0.9f;
	gunSpr->isNonCamera = true;
	gunSpr->zOrder = 30;

	runBtn = ObjectList::GetInstance()->AddObject(new Sprite("Resources/InGame_Ui/Run_Btn_1.png"));
	runBtn->position = App::GetInstance()->screenSize * 0.9f;
	runBtn->position.x -= 300.f;
	runBtn->isNonCamera = true;
	
	runBtn->zOrder = 30;

	attackBtn = ObjectList::GetInstance()->AddObject(new Sprite("Resources/InGame_Ui/Attack_Btn_1.png"));
	attackBtn->position = App::GetInstance()->screenSize * 0.9f + Vec2(100.f, 0.f);
	attackBtn->position.x -= 300.f;
	attackBtn->isNonCamera = true;

	attackBtn->zOrder = 30;

	hpText = ObjectList::GetInstance()->AddObject(new Font(80, L"Arial", L"100/100"));
	hpText->position.x = App::GetInstance()->screenSize.x * 0.1f + 10.f;
	hpText->position.y = App::GetInstance()->screenSize.y * 0.75f;
	hpText->zOrder = 30;
}

void Game::CreateMap()
{
	if (GameManager::GetInstance()->stage == 1)
	{
		auto tile = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile_2/Tile_1.png"));
		tile->position = App::GetInstance()->screenSize * 0.5f;
		tile->zOrder = 0;

		CreateSprite("Resources/Map/Tile_2/Object_1.png", App::GetInstance()->screenSize * 0.5f, 0.f, 3);

		CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(100.f, 420.f), 0.f, 7);
		CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(400.f, 620.f), 0.f, 7);
		CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(700.f, 820.f), 0.f, 7);
		CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(1000.f, 1020.f), 0.f, 7);
		CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(1300.f, 1220.f), 0.f, 7);

		//CreateSprite("Resources/Map/Wall/Wall_1.png", Vec2(480.f, 200.f), 0.f, 9);

		CreateHouse("Resources/Map/Shelf/Shelf_1.png", Vec2(400.f, 780.f), 30.f, 8);
		//CreateHouse("Resources/Map/Shelf/Shelf_1.png", Vec2(800.f, 480.f), 30.f, 8);

		CreateHouse("Resources/Map/Shelf/Shelf_1.png", Vec2(600.f, 630.f), 30.f, 6);

		//CreateObstacle(Vec2(480.f, 300.f), Vec2(1.f, 1.5f), 30);
		CreateObstacle(Vec2(100.f, 520.f), Vec2(1.f, 1.5f), 30);
		CreateObstacle(Vec2(-300.f, 750.f), Vec2(8.f, 1.5f), -30);

		CreateObstacle(Vec2(480.f, 100.f), Vec2(60.f, 1.5f), -30);
		CreateObstacle(Vec2(1000.f, 300.f), Vec2(60.f, 1.f), 30);
		CreateObstacle(Vec2(500.f, 1500.f), Vec2(60.f, 1.f), -30);
	}

	if(GameManager::GetInstance()->stage == 2)
	{
		auto tile = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/Tile_1.png"));
		tile->position = App::GetInstance()->screenSize * 0.5f;
		tile->zOrder = 0;

		auto tree = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/Tree_1.png"));
		tree->position = App::GetInstance()->screenSize * 0.5f;
		tree->zOrder = 8;

		auto ep = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/ElectricPole_1.png"));
		ep->position = App::GetInstance()->screenSize * 0.5f;
		ep->zOrder = 9;

		auto wall_1 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/Wall_1.png"));
		wall_1->position = App::GetInstance()->screenSize * 0.5f;
		wall_1->zOrder = 1;

		auto wall_2 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/Rock_1.png"));
		wall_2->position = App::GetInstance()->screenSize * 0.5f;
		wall_2->zOrder = 1;

		auto wall_3 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Tile/Hill_1.png"));
		wall_3->position = App::GetInstance()->screenSize * 0.5f;
		wall_3->zOrder = 1;

		auto water = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/Water/Water_1.png"));
		water->position = Vec2(-400.f, -650.f);
		water->zOrder = -1;

		auto ani = new Animation(water, 0.1f, true);
		for(size_t i = 1; i < 11; i ++)
		{
			ani->AddFrame("Resources/Map/Water/Water_" + to_string(i) + ".png");
		}

		AnimationManager::GetInstance()->AddAnimation(ani);

		CreateObstacle(Vec2(1200.f, 200.f), Vec2(6.f, 1.f), 30);
		CreateObstacle(Vec2(100.f, 200.f), Vec2(60.f, 1.f), 30);
		CreateObstacle(Vec2(1400.f, 0.f), Vec2(60.f, 1.f), 30);
		CreateObstacle(Vec2(1200.f, 500.f), Vec2(60.f, 1.f), -30);

		CreateHouse("Resources/Map/House/Building_1.png", Vec2(-400.f, -650.f), 0, 2);
		CreateHouse("Resources/Map/House/Building_2.png", Vec2(-200.f, 0.f), -30, 2);
		CreateHouse("Resources/Map/House/Building_5.png", Vec2(950.f, -100.f), -30, 2);

		policeHouse = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map/House/Building_6.png"));
		policeHouse->position = Vec2(800.f, -350.f);
		policeHouse->rotation = D3DXToRadian(30);
		policeHouse->name = "Police";
		policeHouse->zOrder = 2;

		auto icon = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Police_icon/Police_icon_0001.png"));
		icon->position = policeHouse->position + Vec2(0.f, -100.f);
		icon->zOrder = 3;

		auto iconAni = new Animation(icon, 0.1f, true);
		for(size_t i = 1; i < 10; i ++)
		{
			iconAni->AddFrame("Resources/Police_icon/Police_icon_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(iconAni);

		CreateHouse("Resources/Map/House/Building_7.png", Vec2(1750.f, 50.f), -30, 2);
	}
}

void Game::CreateEnemy()
{
	for(size_t i = 0; i < 3; i++)
	{
		auto enemy = ObjectList::GetInstance()->AddObject(new Robot_1());
		enemy->scale *= 0.55f;
		enemy->Init();
		enemys.push_back(enemy);
		enemy->zOrder = 5;
		enemy->position = App::GetInstance()->screenSize * 0.3f + Vec2(rand() % 300 - 150, rand() % 300 - 150);
	}

	for (size_t i = 0; i < 3; i++)
	{
		auto enemy = ObjectList::GetInstance()->AddObject(new Robot_2());
		enemy->scale *= 0.55f;
		enemy->Init();
		enemys.push_back(enemy);
		enemy->zOrder = 5;
		enemy->position = App::GetInstance()->screenSize * 0.3f + Vec2(rand() % 300 - 150, rand() % 300 - 150);
	}

	if(GameManager::GetInstance()->stage == 2)
	{
		auto c = ObjectList::GetInstance()->AddObject(new ControlUnit());
		c->Init();
		enemys.push_back(c);
		c->zOrder = 5;
		c->position = App::GetInstance()->screenSize * 0.3f + Vec2(rand() % 300 - 150, rand() % 300 - 150);
	}
}

void Game::CheckTime()
{
	if(GameManager::GetInstance()->timeStop) { return; }

	time += App::GetInstance()->deltaTime;
	if(time >= 1.f)
	{
		clock -= 1;
		wstring str = to_wstring(clock / 60);
		str += L":";
		str += to_wstring(clock%60);
		count->text = str;
		time = 0.f;
	}
}

void Game::CheckEnemy()
{
	for(auto it = enemys.begin(); it != enemys.end();)
	{
		if((*it)->isRemoved)
		{
			it = enemys.erase(it);
			GameManager::GetInstance()->score += 1000.f;
		}
		else
		{
			it++;
		}
	}

	for(size_t i = 0; i < enemys.size(); i ++)
	{
		Vec2 dir = player->position - enemys[i]->position;
		auto tmp = dynamic_pointer_cast<Enemy>(enemys[i]);
		
		if( 300.f >= D3DXVec2Length(&(dir)))
		{
			if(tmp != nullptr)
			{
				tmp->Detected();
			}
		}
		else
		{
			tmp->None();
		}
	}

	if(DXUTWasKeyPressed(VK_F1))
	{

	}

	if(enemys.size() == 0 || DXUTWasKeyPressed(VK_F2))
	{
		if(!GameManager::GetInstance()->result)
		{
			GameManager::GetInstance()->result = true;
		}
	}

	if(DXUTWasKeyPressed(VK_F3))
	{
		SceneManager::GetInstance()->Change(new ResultScene());
	}
}

void Game::CreateSprite(const string & name, const Vec2 & pos, float rotation, int zOrder)
{
	auto spr = ObjectList::GetInstance()->AddObject(new Sprite(name));
	spr->rotation = D3DXToRadian(rotation);
	spr->position = pos;
	spr->zOrder = zOrder;
}

void Game::CreateHouse(const string& name, const Vec2& pos, float rotation, int zOrder)
{
	auto house = ObjectList::GetInstance()->AddObject(new Sprite(name));
	house->position = pos;
	house->rotation = D3DXToRadian(rotation);
	house->name = "Obstacle";
	house->zOrder = zOrder;
}

void Game::CreateObstacle(const Vec2 & position, const Vec2 & scale, float rotation)
{
	auto obstacle = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Obstacle.png"));
	obstacle->position = position;
	obstacle->name = "Obstacle";
	obstacle->rotation = D3DXToRadian(rotation);
	obstacle->scale = scale;
	obstacle->zOrder = 5;
	obstacle->isVisible = false;
}
