#include "DXUT.h"
#include"Precompile.h"
#include "Game.h"
#include"Player.h"
#include"Enemy.h"
#include"Snow.h"
#include"HpBar.h"
#include"GameManager.h"
#include"Main.h"
#include"Zone.h"

void Game::Enter()
{
	Scene::Enter();
}

void Game::Update()
{
	switch (phase)
	{
	case Game::LOADING_1:
	{
		LoadingScene();
		phase = LOADING_2;
	}
		return;
	case Game::LOADING_2:
		Load();
		phase = LOADING_3;
		return;
	case Game::LOADING_3:
		EnemyLoad();
		phase = LOADING_4;
		return;
	case Game::LOADING_4:
		loading->isRemoved = true;
		loadingBar->isRemoved = true;
		phase = PLAYING;
		return;
	case Game::PLAYING:
	{
		if(!camera->shaking)
		{
			camera->position = player->position;
		}

		int i = 0;
		for(auto enemy : enemys)
		{
			if(enemy->isRemoved)
			{
				i ++;
			}
		}

		if((enemys.size() == i && !isWin) || DXUTWasKeyPressed(VK_F1))
		{
			for (auto enemy : enemys)
			{
				if (enemy->isRemoved)
				{
					enemy->Die();
				}
			}

			isWin = true;
			Win();
		}

		if(DXUTWasKeyPressed(VK_SPACE))
		{
			time -= 60.f;
		}

		if(0.f >= time)
		{
			time = 0.f;
			player->state = Player::DIE;
		}

		if(player->state == Player::DIE && !isLose)
		{
			isLose = true;
			camera->timers.push_back(Timer([&]()
			{
				Lose();
			}, 3.f));
		}

		if(isWin)
		{
			if(1.f > resultPopUp->scale.y)
			{
				resultPopUp->scale.y += App::GetInstance()->deltaTime;
			}

			if(App::GetInstance()->mouseClick && resultPopUp->scale.y >= 1.f)
			{
				if (GameManager::GetInstance()->stage == 3)
				{
					SceneManager::GetInstance()->Change(new Main());
				}
				else
				{
					SceneManager::GetInstance()->Change(new Game());
				}
			}
		}
		else if(isLose)
		{
			if (App::GetInstance()->mouseClick)
			{
				SceneManager::GetInstance()->Change(new Main());
			}
		}

		hpBar->SetValue(player->hp / player->maxHp);
		staminaBar->SetValue(player->stamina / player->maxStamina);
	}
		break;
	}
	SetTime();

	if(player->weapon == Player::RIFLE)
	{
		weaponSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Weapon_2.png");
	}
	else if(player->weapon == Player ::LAZER)
	{
		weaponSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Weapon_1.png");
	}

	if(player->hp <= 30.f)
	{
		hpLow->isVisible = true;	
	}
	else
	{
		hpLow->isVisible = false;
	}

	if(DXUTIsKeyDown(VK_SHIFT))
	{
		shiftSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Ingame_UI/Run_Btn_2.png");
	}
	else
	{
		shiftSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Ingame_UI/Run_Btn_1.png");
	}

	if (DXUTIsKeyDown('J'))
	{
		jSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Ingame_UI/Click_Btn_2.png");
	}
	else
	{
		jSpr->tex = TextureManager::GetInstance()->LoadTexture("Resources/Ingame_UI/Click_Btn_1.png");
	}

	if(GameManager::GetInstance()->isStop)
	{
		stopEffect->isVisible = true;
	}
	else
	{
		stopEffect->isVisible = false;
	}

	hpFont->text = to_wstring((int)player->hp);

	for(size_t i = 0; i < enemys.size(); i ++)
	{
		if (enemys[i]->isDie)
		{
			arrows[i]->isVisible = false;
		}

		Vec2 vec = enemys[i]->position - player->position;
		if(D3DXVec2Length(&(Vec2(player->position - enemys[i]->position))) < 1100.f)
		{
			arrows[i]->isVisible = false;
		}
		else
		{
			arrows[i]->isVisible = true;
		}

		arrows[i]->position = player->position;
		arrows[i]->position.y += 40.f;
		arrows[i]->rotation = atan2(vec.y, vec.x);
	}
}

void Game::Exit()
{
}

void Game::LoadingScene()
{
	loading = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Loading/Loading_Bg.png"), true, true);
	loading->position = App::GetInstance()->screenSize * 0.5f;
	loading->zOrder = 500;
	loading->isNonCamera = true;

	loadingBar = ObjectList::GetInstance()->AddObject(new ProgressBar("Resources/Loading/Loading_Bar.png"), true, true);
	loadingBar->position.x = App::GetInstance()->screenSize.x * 0.5f;
	loadingBar->position.y = App::GetInstance()->screenSize.y * 0.9f;
	loadingBar->zOrder = 500;
	loadingBar->isNonCamera = true;

	loadingBar->SetValue(0.f);
}

void Game::Load()
{
	loadingBar->SetValue(0.3f);

	for (size_t i = 0; i < 17; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Hp_Get/Hp_Get_" + to_string(i) + ".png");
	}

	for (size_t i = 0; i < 17; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Weapon_Get/Weapon_Get_" + to_string(i) + ".png");
	}

	switch (GameManager::GetInstance()->stage)
	{
	case 1:
	{
		auto background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Background/Map_1_Bg.png"), false);
		auto obstacles = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Background/Map_1_Wall_4.png"), false);

		for (size_t i = 0; i < 6; i++)
		{
			auto a = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Background/Map_1_Wall_2.png"));
			a->position = RealPosition(Vec2(-428.104, -1201.961 + (i * 500)));
			a->name = "Obstacle";
		}

		for (size_t i = 0; i < 5; i++)
		{
			auto a = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Background/Map_1_Wall_1.png"));
			a->position = RealPosition(Vec2(54.541, -933.592 + (i * 500)));
			a->name = "Obstacle";
		}

		for (size_t i = 0; i < 4; i++)
		{
			CreateObstacle("Resources/Background/Map_1_Wall_2.png", Vec2(15.812 + (i * 500), 271.523), true);
		}

		CreateObstacle("Resources/Background/Map_1_Wall_1.png", Vec2(791.078, 937.136), true);
		CreateObstacle("Resources/Background/Map_1_Wall_1.png", Vec2(791.078 + 500, 937.136), true);
		CreateObstacle("Resources/Background/Map_1_Wall_3.png", Vec2(1550.375, 640.644), true);
		CreateObstacle("Resources/Background/Map_1_Wall_1.png", Vec2(791.078, 538.491), true);

		CreateObstacle("Resources/Background/Obstacle_Under.png", Vec2(-600.f, -1602.358));
		CreateObstacle("Resources/Background/1.png", Vec2(-1836.053, -1201.961));
		CreateObstacle("Resources/Background/2.png", Vec2(-1474.634, 643.744));
		CreateObstacle("Resources/Background/3.png", Vec2(-993.684, 1264.905));
		CreateObstacle("Resources/Background/4.png", Vec2(-159.147, 2083.913));
		CreateObstacle("Resources/Background/5.png", Vec2(712.115, 1553.389));
		CreateObstacle("Resources/Background/6.png", Vec2(1085.297, 1247.014));
		CreateObstacle("Resources/Background/7.png", Vec2(1744.261, 437.336));
		CreateObstacle("Resources/Background/8.png", Vec2(1203.123, -271.83));
		CreateObstacle("Resources/Background/9.png", Vec2(723.606, -1291.529));

	}
		break;

	case 2:
	{
		auto water = ObjectList::GetInstance()->AddObject(new Sprite("Resources/water.png"), false);

		auto background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map_2/Map_2_tile.png"), false);
		
		auto map2obj = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map_2/Map_2_Object.png"), false);
		auto map2obj_2 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map_2/Map_2_Wall_1.png"), false);
		auto map2obj_3 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Map_2/Map_2_Wall_2.png"), false);

		CreateObstacle("Resources/Map_2/Map_2_House_1.png", Vec2(-483.535, 35.715), true);
		CreateObstacle("Resources/Map_2/Map_2_House_2.png", Vec2(-542.367, 870.441), true);
		CreateObstacle("Resources/Map_2/Map_2_House_3.png", Vec2(-854.664, 1328.009), true);
		CreateObstacle("Resources/Map_2/Map_2_House_4.png", Vec2(-281.805, 2410.304), true);
		CreateObstacle("Resources/Map_2/Map_2_House_5.png", Vec2(362.663, 1242.889), true);
		CreateObstacle("Resources/Map_2/Map_2_House_6.png", Vec2(646.008, 300.393), true);
		CreateObstacle("Resources/Map_2/Map_2_House_7.png", Vec2(488.117, -610.743), true);
		CreateObstacle("Resources/Map_2/Map_2_House_8.png", Vec2(1577.261, 708.52), true);

		auto hpZone = ObjectList::GetInstance()->AddObject(new HealZone());
		hpZone->position = RealPosition(Vec2(1377.261, 758.52));
		hpZone->Init();

		auto weaponZone = ObjectList::GetInstance()->AddObject(new WeaponZone());
		weaponZone->position = RealPosition(Vec2(362.663, 942.889));
		weaponZone->Init();

		auto hpIcon = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hp_Weapon/HpIcon_0000.png"), true, true);
		hpIcon->position = RealPosition(Vec2(1577.261, 958.52));
		
		auto ani = new Animation(hpIcon, 0.1f, true);
		for(size_t i = 0; i < 10; i ++)
		{
			ani->AddFrame("Resources/Hp_Weapon/HpIcon_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);

		auto weaponIcon = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Hp_Weapon/Weapon_0000.png"), true, true);
		weaponIcon->position = RealPosition(Vec2(362.663, 1392.889));

		auto weaponAni = new Animation(weaponIcon, 0.1f, true);
		for (size_t i = 0; i < 10; i++)
		{
			weaponAni->AddFrame("Resources/Hp_Weapon/Weapon_000" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(weaponAni);

		auto tree_1 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_5.png"), true, true);
		tree_1->name = "Tree";
		tree_1->position = RealPosition(Vec2(-1431.13, 546.208));

		auto tree_2 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_6.png"), true, true);
		tree_2->name = "Tree";
		tree_2->position = RealPosition(Vec2(-1684.589, -1384.681));

		auto tree_3 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_7.png"), true, true);
		tree_3->name = "Tree";
		tree_3->position = RealPosition(Vec2(-852.468, -1497.853));

		auto tree_4 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_8.png"), true, true);
		tree_4->name = "Tree";
		tree_4->position = RealPosition(Vec2(1440.371, -1425.058));

		auto tree_5 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_9.png"), true, true);
		tree_5->name = "Tree";
		tree_5->position = RealPosition(Vec2(474.735, -1659.307));

		auto tree_6 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_10.png"), true, true);
		tree_6->name = "Tree";
		tree_6->position = RealPosition(Vec2(1679.265, 14.232));

		auto tree_7 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_11.png"), true, true);
		tree_7->name = "Tree";
		tree_7->position = RealPosition(Vec2(1413.353, 1303.273));

		auto tree_8 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Tree/Map_2_Tree_12.png"), true, true);
		tree_8->name = "Tree";
		tree_8->position = RealPosition(Vec2(499.63, -103.859));
	}
		break;
	}
	
	weaponSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Weapon_2.png"), true, true);
	weaponSpr->position = App::GetInstance()->screenSize * 0.9f;
	weaponSpr->isNonCamera = true;
	weaponSpr->zOrder = 2;

	shiftSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Ingame_UI/Run_Btn_1.png"), true, true);
	shiftSpr->position = Vec2(App::GetInstance()->screenSize.x * 0.7f, App::GetInstance()->screenSize.y * 0.9f);
	shiftSpr->isNonCamera = true;
	shiftSpr->zOrder = 2;

	jSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Ingame_UI/Click_Btn_1.png"), true, true);
	jSpr->position = Vec2(App::GetInstance()->screenSize.x * 0.75f, App::GetInstance()->screenSize.y * 0.9f);
	jSpr->isNonCamera = true;
	jSpr->zOrder = 2;

	if(GameManager::GetInstance()->stage == 2)
	{
		auto mission = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Time_2.png"), true, true);
		mission->position = App::GetInstance()->screenSize * 0.5f;
		mission->isNonCamera = true;
		mission->zOrder = 2;
	}
	else
	{
		auto mission = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Time_1.png"), true, true);
		mission->position = App::GetInstance()->screenSize * 0.5f;
		mission->isNonCamera = true;
		mission->zOrder = 2;
	}

	timeFont = ObjectList::GetInstance()->AddObject(new Font(40, L"Arial", to_wstring(time)), true, true);
	timeFont->isNonCamera = true;
	if(GameManager::GetInstance()->stage == 2)
	{
		timeFont->position = Vec2(App::GetInstance()->screenSize.x * 0.37f, App::GetInstance()->screenSize.y * 0.05f - 12.f);
	}
	else { timeFont->position = Vec2(App::GetInstance()->screenSize.x * 0.4f, App::GetInstance()->screenSize.y * 0.05f - 12.f); }
	timeFont->color = Color(1.f, 0.8f, 0.f, 1.f);
	timeFont->zOrder = 2;

	auto icon = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Icon/Icon_1.png"), true, true);
	icon->isNonCamera = true;
	icon->position.x = 126;
	icon->position.y = 940;
	icon->zOrder = 2;

	auto ani = new Animation(icon, 0.1f, true);
	for(size_t i = 1; i < 20; i ++)
	{
		ani->AddFrame("Resources/Icon/Icon_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	hpBar = ObjectList::GetInstance()->AddObject(new PlayerHpBar(), true, true);
	hpBar->isNonCamera = true;
	hpBar->position = Vec2(370, 958);
	hpBar->zOrder = 2;

	staminaBar = ObjectList::GetInstance()->AddObject(new PlayerStaminaBar(), true, true);
	staminaBar->isNonCamera = true;
	staminaBar->position = Vec2(365, 1007);
	staminaBar->zOrder = 2;

	player = ObjectList::GetInstance()->AddObject(new Player());
	player->position = App::GetInstance()->screenSize * 0.2f;
	player->zOrder = 1;
	player->Init();

	hpFont = ObjectList::GetInstance()->AddObject(new Font(80, L"Arial", to_wstring((int)player->hp)), true, true);
	hpFont->isNonCamera = true;
	hpFont->position = Vec2(App::GetInstance()->screenSize.x * 0.2f - 150.f, App::GetInstance()->screenSize.y * 0.85f - 60.f);
	hpFont->zOrder = 2;

	auto maxHpSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/100.png"), true, true);
	maxHpSpr->isNonCamera = true;
	maxHpSpr->position = Vec2(383, 917);
	maxHpSpr->zOrder = 2;

	hpLow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/HpLow/HpLow_1.png"), true, true);
	hpLow->position = App::GetInstance()->screenSize * 0.5f;
	hpLow->isVisible = false;
	hpLow->isNonCamera = true;

	auto _ani = new Animation(hpLow, 0.1f, true);
	for(size_t i = 0; i < 6; i ++)
	{
		_ani->AddFrame("Resources/HpLow/HpLow_" + to_string(i + 1) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(_ani);
	
	stopEffect = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Time_Bg/Time_Bg_1.png"), true, true);
	stopEffect->isVisible = false;
	stopEffect->isNonCamera = true;
	stopEffect->position = App::GetInstance()->screenSize * 0.5f;
	stopEffect->color = Color(0.f, 1.f, 1.f, 1.f);

	auto __ani = new Animation(stopEffect, 0.1f, true);

	for (size_t i = 1; i < 7; i++)
	{
		__ani->AddFrame("Resources/Time_Bg/Time_Bg_" + to_string(i + 1) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(__ani);
}

void Game::EnemyLoad()
{
	loadingBar->SetValue(0.6f);

	if(GameManager::GetInstance()->stage == 1)
	{
		CreateEnemy(1, Vec2(-803.565, -622.122));
		CreateEnemy(1, Vec2(0.043, 918.363));
		CreateEnemy(1, Vec2(606.186, 246.271));
		CreateEnemy(2, Vec2(-637.046, 1209.953));

 		auto spr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Objective/Objective_1/Objective_1.png"), true, true);
		spr->isNonCamera = true;
		spr->position = App::GetInstance()->screenSize * 0.5f;
		spr->zOrder = 555;
		auto ani = new Animation(spr, 0.1f, false);
		for(size_t i = 1; i < 30; i ++)
		{
			ani->AddFrame("Resources/Objective/Objective_1/Objective_" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}
	else if(GameManager::GetInstance()->stage == 2)
	{
		CreateEnemy(1, Vec2(-803.565, -622.122));
		auto boss = ObjectList::GetInstance()->AddObject(new Boss());
		boss->position = RealPosition(Vec2(-1645.743, -507.447));
		boss->Init();
		enemys.push_back(boss);

		auto spr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Objective/Objective_2/Objective_1.png"), true, true);
		spr->isNonCamera = true;
		spr->position = App::GetInstance()->screenSize * 0.5f;
		spr->zOrder = 555;
		auto ani = new Animation(spr, 0.1f, false);
		for (size_t i = 1; i < 30; i++)
		{
			ani->AddFrame("Resources/Objective/Objective_2/Objective_" + to_string(i) + ".png");
		}
		AnimationManager::GetInstance()->AddAnimation(ani);
	}

	for(size_t i = 0; i < enemys.size(); i ++)
	{
		auto arrow = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Under_Light2.png"), false);
		arrow->scale *= 0.5f;
		arrow->pivot = Vec3(0.f, arrow->tex->r.bottom * 0.5f, 0.f);
		arrows.push_back(arrow);
	}
}

void Game::Win()
{
	GameManager::GetInstance()->stage++;

	auto snow = ObjectList::GetInstance()->AddObject(new Snow(0.1f, 200.f));

	auto bg = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Result_Bg.png"), true, true);
	bg->isNonCamera = true;
	bg->position = App::GetInstance()->screenSize * 0.5f;
	if(GameManager::GetInstance()->stage == 3)
	{
		bg->tex = TextureManager::GetInstance()->LoadTexture("Resources/Result2_Bg.png");
	}
	bg->zOrder = 500;

	resultPopUp = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Result_PopUP.png"), true, true);
	resultPopUp->scale.y = 0.f;
	resultPopUp->isNonCamera = true;
	resultPopUp->position = App::GetInstance()->screenSize * 0.5f;
	resultPopUp->zOrder = 501;

	auto pyr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Win/Ct_Win_0170.png"), true, true);
	pyr->isNonCamera = true;
	pyr->position.x += 700.f;
	pyr->position.y += 500.f;
	pyr->zOrder = 501;

	auto ani = new Animation(pyr, 0.1f, true);

	for (size_t i = 170; i < 186; i++)
	{
		ani->AddFrame("Resources/Win/Ct_Win_0" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	auto light = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Win/Ct_Win_0170.png"), true, true);
	light->isNonCamera = true;
	light->position = App::GetInstance()->screenSize * 0.5f;
	light->zOrder = 501;

	auto _ani = new Animation(light, 0.1f, true);

	for (size_t i = 1; i < 9; i++)
	{
		_ani->AddFrame("Resources/_Light/Light_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(_ani);


	bg->timers.push_back(Timer([&]()
	{
		auto text = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Text_1.png"), true, true);
		text->isNonCamera = true;
		text->position.x = App::GetInstance()->screenSize.x * 0.8f;
		text->position.y = App::GetInstance()->screenSize.y * 0.15f;
		text->zOrder = 501;

		auto anyKey = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Text_2.png"), true ,true);
		anyKey->isNonCamera = true;
		anyKey->position.x = App::GetInstance()->screenSize.x * 0.8f;
		anyKey->position.y = App::GetInstance()->screenSize.y * 0.9f;
		anyKey->zOrder = 501;

		auto ani = new Animation(anyKey, 0.3f, true);
		ani->AddFrame("Resources/Result/Text_2.png");
		ani->AddFrame("Resources/Result/Text_3.png");
		AnimationManager::GetInstance()->AddAnimation(ani); 
	}, 2.f));

	bg->timers.push_back(Timer([&]()
	{
		auto text = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Text_4.png"), true, true);
		text->isNonCamera = true;
		text->position = App::GetInstance()->screenSize * 0.5f;
		text->zOrder = 501;

	}, 3.f));

	bg->timers.push_back(Timer([&]()
	{
		auto f = ObjectList::GetInstance()->AddObject(new Font(50.f, L"Arial", to_wstring(time * 1234)), true, true);
		f->isNonCamera = true;
		f->position.x = App::GetInstance()->screenSize.x * 0.8f;
		f->position.y = App::GetInstance()->screenSize.y * 0.53f;
		f->zOrder = 502;

		auto fo = ObjectList::GetInstance()->AddObject(new Font(50.f, L"Arial", timeFont->text), true, true);
		fo->isNonCamera = true;
		fo->position.x = App::GetInstance()->screenSize.x * 0.8f;
		fo->position.y = App::GetInstance()->screenSize.y * 0.37f;

		fo->zOrder = 502;
	}, 4.f));
}

void Game::Lose()
{
	auto bg = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Result_Bg.png"), true, true);
	bg->isNonCamera = true;
	bg->position = App::GetInstance()->screenSize * 0.5f;
	if (GameManager::GetInstance()->stage == 3)
	{
		bg->tex = TextureManager::GetInstance()->LoadTexture("Resources/Result2_Bg.png");
	}
	bg->zOrder = 500;

	auto pyr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Fail/Fail_0190.png"), true, true);
	pyr->isNonCamera = true;
	pyr->scale *= 0.8f;
	pyr->position.x += 700.f;
	pyr->position.y += 500.f;
	pyr->zOrder = 501;

	auto ani = new Animation(pyr, 0.1f, true);

	for (size_t i = 190; i < 211; i++)
	{
		ani->AddFrame("Resources/Fail/Fail_0" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	resultPopUp = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Result_PopUP.png"), true, true);
	resultPopUp->scale.y = 0.f;
	resultPopUp->isNonCamera = true;
	resultPopUp->position = App::GetInstance()->screenSize * 0.5f;
	resultPopUp->zOrder = 3;
	resultPopUp->zOrder = 501;

	bg->timers.push_back(Timer([&]()
	{
		auto text = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Text_5.png"), true, true);
		text->isNonCamera = true;
		text->position.x = App::GetInstance()->screenSize.x * 0.8f;
		text->position.y = App::GetInstance()->screenSize.y * 0.15f;
		text->zOrder = 502;
	}, 2.f));
}

Vec2 Game::RealPosition(const Vec2& pos)
{
	Vec2 _pos;

	if(GameManager::GetInstance()->stage == 1)
	{
		_pos = Vec2((4615 / 2) / 2210.399  * pos.x, (4300 / 2) / -2798.294  * pos.y);
	}
	else if(GameManager::GetInstance()->stage == 2)
	{
		_pos = Vec2((4538 / 2) / 2210.399  * pos.x, (3925 / 2) / -2798.294  * pos.y);
	}

	return _pos;
}

void Game::CreateObstacle(const string& name, const Vec2 & pos, bool visible)
{
	auto obstacle = ObjectList::GetInstance()->AddObject(new Sprite(name));
	obstacle->position = RealPosition(pos);
	obstacle->name = "Obstacle";
	obstacle->isVisible = visible;
}

void Game::CreateEnemy(int id, const Vec2 & position)
{
	switch(id)
	{
	case 1:
	{
		auto testEnemy = ObjectList::GetInstance()->AddObject(new Enemy_1());
		testEnemy->position = RealPosition(position);
		testEnemy->Init();
		enemys.push_back(testEnemy);
	}
		break;

	case 2:
	{
		auto test = ObjectList::GetInstance()->AddObject(new Enemy_2());
		test->position = RealPosition(position);
		test->Init();
		enemys.push_back(test);
	}
	break;
	}
}

void Game::SetTime()
{
	if(!GameManager::GetInstance()->isStop)
	{
		timeTime = timeTime + App::GetInstance()->deltaTime;
		if (timeTime >= 1.f)
		{
			time -= 1;
			timeTime = 0.f;
		}
	}

	wchar_t buffer[256];
	swprintf(buffer, 256, L"%02d : %02d", time / 60, time % 60);

	wstring text = buffer;
	timeFont->text = text;
}
