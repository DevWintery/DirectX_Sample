#include "DXUT.h"
#include"Precompile.h"
#include "Outro.h"
#include"Result.h"

void Outro::Enter()
{
	Scene::Enter();

	auto out = ObjectList::GetInstance()->AddObject(new Sprite("Resources/Out/Out_10000"));
	out->position = App::GetInstance()->screenSize * 0.5f;
	out->isNonCamera = true;

	fade = ObjectList::GetInstance()->AddObject(new Sprite("Resources/3.png"), true ,true);
	fade->isVisible = false;
	fade->isNonCamera = true;
	fade->position = App::GetInstance()->screenSize * 0.5f;
	fade->color.a = 0.f;

	auto _ani = new Animation(out, 0.15f, false);
	
	for(size_t i = 0; i < 26; i ++)
	{
		_ani->AddFrame("Resources/Out/Out_" + to_string( 10000 + i ) + ".png");
	}
	ani = AnimationManager::GetInstance()->AddAnimation(_ani);
}

void Outro::Update()
{
	if(ani->isDone)
	{
		fade->isVisible = true;
		fade->color.a += 0.5f * App::GetInstance()->deltaTime;
	}

	if(fade->color.a >= 1.f)
	{
		SceneManager::GetInstance()->Change(new Result());
	}
}
