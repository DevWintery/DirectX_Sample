#include"DXUT.h"
#include"Precompile.h"
#include"Intro.h"
#include"Main.h"

Intro::Intro():
	rate(3.f), time(0.f)
{
}

Intro::~Intro()
{
}

void Intro::Enter()
{
	Scene::Enter();

	for (size_t i = 10; i < 42; i++)
	{
		TextureManager::GetInstance()->LoadTexture("Resources/Intro/Intro00" + to_string(i) + ".png");
	}

	auto introImage = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Intro/Intro0000.png"));
	introImage->position = App::GetInstance()->screenSize * 0.5f;

	auto ani = new Animation(introImage, 0.2f, false);
	for (size_t i = 0; i < 10; i++)
	{
		ani->AddFrame("Resources/Intro/Intro000" + to_string(i) + ".png");
	}
	for(size_t i = 10; i < 42; i ++)
	{
		ani->AddFrame("Resources/Intro/Intro00" + to_string(i) + ".png");
	}
	introAni = AnimationManager::GetInstance()->AddAnimation(ani);

	TextureManager::GetInstance()->LoadTexture("Loading/Loading_1.png");
}

void Intro::Update()
{
	if(introAni->count == introAni->curIndex)
	{
		SceneManager::GetInstance()->Change(new Main());
	}
}

void Intro::Exit()
{
	Scene::Exit();
}
