#include"DXUT.h"
#include"Precompile.h"
#include"Main.h"
#include"Game.h"
#include"GameManager.h"

Main::Main()
{
}

Main::~Main()
{
}

void Main::Enter()
{
	Scene::Enter();

	GameManager::GetInstance()->stage = 1;

	auto background = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_1/Main_1.png"));
	background->position = App::GetInstance()->screenSize * 0.5f;

	auto ani = new Animation(background, 0.2f, true);
	for(size_t i = 1; i < 15; i ++)
	{
		ani->AddFrame("Resources/Main_1/Main_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(ani);

	auto title = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_2/Main_UI_1.png"));
	title->position = App::GetInstance()->screenSize * 0.5f;
	
	auto tAni = new Animation(title, 0.1f, false);
	for (size_t i = 1; i < 11; i++)
	{
		tAni->AddFrame("Resources/Main_2/Main_UI_" + to_string(i) + ".png");
	}
	AnimationManager::GetInstance()->AddAnimation(tAni);

	auto btnBG = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_3/Main_BtnBg_1.png"));
	btnBG->position = App::GetInstance()->screenSize * 0.5f;

	auto spr_1 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_3/1_Btn_1.png"));
	spr_1->position = App::GetInstance()->screenSize * 0.5f;

	auto spr_2 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_3/2_Btn_1.png"));
	spr_2->position = App::GetInstance()->screenSize * 0.5f;

	auto spr_3 = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_3/3_Btn_1.png"));
	spr_3->position = App::GetInstance()->screenSize * 0.5f;

	auto gameBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_3/1_Btn_4.png", [&]() { SceneManager::GetInstance()->Change(new Game());}));
	gameBtn->position.x = App::GetInstance()->screenSize.x * 0.375f;
	gameBtn->position.y = App::GetInstance()->screenSize.y * 0.55f;
	gameBtn->highlightTexture = TextureManager::GetInstance()->LoadTexture("Resources/Main_3/1_Btn_2.png");

	auto introBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_3/2_Btn_4.png", [&]() 
	{
		introducePopUp->isVisible = true;
		helpPopUp->isVisible = false;
		closeBtn->isVisible = true;
	}));
	introBtn->position.x = App::GetInstance()->screenSize.x * 0.625f;
	introBtn->position.y = App::GetInstance()->screenSize.y * 0.55f;
	introBtn->highlightTexture = TextureManager::GetInstance()->LoadTexture("Resources/Main_3/2_Btn_2.png");

	auto helpBtn = ObjectList::GetInstance()->AddObject(new Button("Resources/Main_3/3_Btn_4.png", [&]()
	{
		introducePopUp->isVisible = false;
		helpPopUp->isVisible = true;
		closeBtn->isVisible = true;
	}));
	helpBtn->position.x = App::GetInstance()->screenSize.x * 0.58f;
	helpBtn->position.y = App::GetInstance()->screenSize.y * 0.7f;
	helpBtn->highlightTexture = TextureManager::GetInstance()->LoadTexture("Resources/Main_3/3_Btn_2.png");

	closeBtn = ObjectList::GetInstance()->AddObject(new Button("closeBtn.png", [&]()
	{
		introducePopUp->isVisible = false;
		helpPopUp->isVisible = false;
		closeBtn->isVisible = false;
	}));
	closeBtn->position.x = App::GetInstance()->screenSize.x * 0.8f;
	closeBtn->position.y = App::GetInstance()->screenSize.y * 0.2f;
	closeBtn->isVisible = false;

	introducePopUp = ObjectList::GetInstance()->AddObject(new Sprite("introPopUp.png"));
	introducePopUp->position = App::GetInstance()->screenSize * 0.5f;
	introducePopUp->isVisible = false;

	helpPopUp = ObjectList::GetInstance()->AddObject(new Sprite("introPopUp.png"));
	helpPopUp->position = App::GetInstance()->screenSize * 0.5f;
	helpPopUp->isVisible = false;
}

void Main::Update()
{
}

void Main::Exit()
{
	Scene::Exit();
}
