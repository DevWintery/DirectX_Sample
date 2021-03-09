#include "DXUT.h"
#include"Precompile.h"
#include "Intro.h"
#include"Main.h"

Intro::Intro()
{
}


Intro::~Intro()
{
}

void Intro::Enter()
{
	Scene::Enter();

	for (size_t i = 1; i < 20; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Main_Ui/Main_" + to_string(i) + ".png");
	}

	for (size_t i = 170; i < 186; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Win/Ct_Win_0" + to_string(i) + ".png");
	}

	for (size_t i = 0; i < 26; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Out/Out_" + to_string(10000 + i) + ".png");
	}


	auto out = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Int/Intro_10017.png"));
	out->position = App::GetInstance()->screenSize * 0.5f;
	out->isNonCamera = true;

	fade = ObjectList::GetInstance()->AddObject(new Sprite("Resources/3.png"), true, true);
	fade->isVisible = false;
	fade->isNonCamera = true;
	fade->position = App::GetInstance()->screenSize * 0.5f;
	fade->color.a = 0.f;

	auto _ani = new Animation(out, 0.15f, false);

	for (size_t i = 17; i < 76; i++)
	{
		_ani->AddFrame("Resources/Int/Intro_" + to_string(10000 + i) + ".png");
	}
	ani = AnimationManager::GetInstance()->AddAnimation(_ani);
}

void Intro::Update()
{
	if (ani->isDone)
	{
		fade->isVisible = true;
		fade->color.a += 0.5f * App::GetInstance()->deltaTime;
	}

	if (fade->color.a >= 1.f)
	{
		SceneManager::GetInstance()->Change(new Main());
	}
}

void Intro::Exit()
{
}
