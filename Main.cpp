#include "DXUT.h"
#include"Precompile.h"
#include "Main.h"
#include"Game.h"
#include"GameManager.h"

void Main::Enter()
{
	Scene::Enter();

	GameManager::GetInstance()->stage = 1;

	camera->scale = Vec2(5.f, 5.f);

	auto bg = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_Ui/Main_Bg.png"));
	bg->position = App::GetInstance()->screenSize * 0.5f;

	cursor = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Mouse_Point.png"), true, true);

	camera->timers.push_back(Timer([&]()
	{
		titleSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_Ui/Main_1"));
		titleSpr->position = App::GetInstance()->screenSize * 0.5f;

		auto ani = new Animation(titleSpr, 0.05f, false);
		for(size_t i = 1; i < 20; i ++)
		{
			ani->AddFrame("Resources/Main_Ui/Main_" + to_string(i) + ".png");
		}
		titleAni = AnimationManager::GetInstance()->AddAnimation(ani);
	}, 2.5f));

	gameBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_Btn/GameStart_Btn_1.png", [&]()
	{
		SceneManager::GetInstance()->Change(new Game());
	}), true, true);
	gameBtn->pushTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameStart_Btn_3.png");
	gameBtn->highlightTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameStart_Btn_2.png");
	
	gameBtn->position = Vec2(-500.f, App::GetInstance()->screenSize.y * 0.45f);

	introBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_Btn/GameInt_Btn_1.png", [&]()
	{
		gameBtn->isVisible = false;
		introBtn->isVisible = false;
		helpBtn->isVisible = false;
		returnBtn->isVisible = false;
		titleSpr->isVisible = false;

		introSpr->isVisible = true;
		waySpr->isVisible = false;
		quitBtn->isVisible = true;
	}), true, true);
	introBtn->pushTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameInt_Btn_3.png");
	introBtn->highlightTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameInt_Btn_2.png");

	introBtn->position = Vec2(-500.f, App::GetInstance()->screenSize.y * 0.6f);

	helpBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_Btn/GameWay_Btn_1.png", [&]()
	{
		gameBtn->isVisible = false;
		introBtn->isVisible = false;
		helpBtn->isVisible = false;
		returnBtn->isVisible = false;
		titleSpr->isVisible = false;

		introSpr->isVisible = false;
		waySpr->isVisible = true;
		quitBtn->isVisible = true;
	}), true, true);
	helpBtn->pushTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameWay_Btn_3.png");
	helpBtn->highlightTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/GameWay_Btn_2.png");

	helpBtn->position = Vec2(-500.f, App::GetInstance()->screenSize.y * 0.75f);

	returnBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_Btn/Quit_Btn_1.png", [&]()
	{
		PostQuitMessage(0);
	}), true, true);
	returnBtn->pushTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/Quit_Btn_3.png");
	returnBtn->highlightTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Btn/Quit_Btn_2.png");

	returnBtn->position = Vec2(-500.f, App::GetInstance()->screenSize.y * 0.9f);

	waySpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_Ui/GameWay_Bg.png"), true, true);
	waySpr->position = App::GetInstance()->screenSize * 0.5f;
	waySpr->isVisible = false;

	introSpr = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_Ui/GameInt_Bg.png"), true, true);
	introSpr->position = App::GetInstance()->screenSize * 0.5f;
	introSpr->isVisible = false;

	quitBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_Ui/Exit_Btn_1.png", [&]()
	{
		gameBtn->isVisible = true;
		introBtn->isVisible = true;
		helpBtn->isVisible = true;
		returnBtn->isVisible = true;
		titleSpr->isVisible = true;

		introSpr->isVisible = false;
		waySpr->isVisible = false;
		quitBtn->isVisible = false;
	}), true, true);
	quitBtn->pushTex = TextureManager::GetInstance()->LoadTexture("Resources/Main_Ui/Exit_Btn_2.png");
	quitBtn->isVisible = false;
	quitBtn->position = Vec2(App::GetInstance()->screenSize.x * 0.8f, App::GetInstance()->screenSize.y * 0.1f);
}

void Main::Update()
{
	cursor->position = App::GetInstance()->mousePosition;
	cursor->zOrder = 600;

	if(camera->scale.x > 1.f)
	{
		camera->scale.x -= App::GetInstance()->deltaTime * speed;
		camera->scale.y -= App::GetInstance()->deltaTime * speed;
		if(camera->scale.x < 1.f)
		{
			camera->scale = Vec2(1.f, 1.f);
		}
		speed += App::GetInstance()->deltaTime * 2;
	}

	if(titleAni != nullptr)
	{
		if(titleAni->isDone)
		{
			D3DXVec2Lerp(&gameBtn->position, &gameBtn->position, &(Vec2(250.f, App::GetInstance()->screenSize.y * 0.45f)), 0.1f);
			D3DXVec2Lerp(&introBtn->position, &introBtn->position, &(Vec2(250.f, App::GetInstance()->screenSize.y * 0.6f)), 0.1f);
			D3DXVec2Lerp(&helpBtn->position, &helpBtn->position, &(Vec2(250.f, App::GetInstance()->screenSize.y * 0.75f)), 0.1f);
			D3DXVec2Lerp(&returnBtn->position, &returnBtn->position, &(Vec2(220.f, App::GetInstance()->screenSize.y * 0.9f)), 0.1f);
		}
	}
}
