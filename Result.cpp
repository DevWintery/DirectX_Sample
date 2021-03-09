#include "DXUT.h"
#include"Precompile.h"
#include "Result.h"

Result::Result()
{
}

Result::~Result()
{
}

void Result::Enter()
{
	Scene::Enter();

	auto main = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Main_Ui/Main_Bg.png"));
	main->position = App::GetInstance()->screenSize * 0.5f;

	auto bg = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Bg.png"));
	bg->position = App::GetInstance()->screenSize * 0.5f;

	auto result = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Ranking_Bg.png"));
	result->position = App::GetInstance()->screenSize * 0.5f;
}

void Result::Update()
{
}

void Result::Exit()
{
}
