#include"DXUT.h"
#include"Precompile.h"
#include"ResultScene.h"
#include"Main.h"
#include"GameManager.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Enter()
{
	Scene::Enter();

	auto bg = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Result/Result_Bg.png"));
	bg->position = App::GetInstance()->screenSize * 0.5f;

	auto btn =  ObjectList::GetInstance()->AddObject(new Button("Resources/Result/Exit_Btn_1.png", [&]() { SceneManager::GetInstance()->Change(new Main()); } ));
	btn->highlightTexture = TextureManager::GetInstance()->LoadTexture("Resources/Result/Exit_Btn_2.png");
	btn->pushTexture = TextureManager::GetInstance()->LoadTexture("Resources/Result/Exit_Btn_3.png");

	btn->position = App::GetInstance()->screenSize * 0.7f;
	btn->position.x -= 50.f;

	auto score = ObjectList::GetInstance()->AddObject(new Font(100, L"Arial", to_wstring(GameManager::GetInstance()->score)));
	score->position.x = App::GetInstance()->screenSize.x * 0.6f + 50.f;
	score->position.y = App::GetInstance()->screenSize.y * 0.45f;
	score->zOrder = 100;
}

void ResultScene::Update()
{
}

void ResultScene::Exit()
{
	Scene::Exit();
}
