#include"DXUT.h"
#include"Precompile.h"
#include"Scene.h"

void SceneManager::Start(Scene * startScene)
{
	curScene = startScene;

	curScene->Enter();
}

void SceneManager::Change(Scene * newScene)
{
	nextScene = newScene;
}

void SceneManager::Update()
{
	if (nextScene != nullptr)
	{
		curScene->Exit();
		SAFE_DELETE(curScene);

		ObjectList::GetInstance()->Release();

		nextScene->Enter();
		curScene = nextScene;
		nextScene = nullptr;
	}

	if (curScene)
	{
		curScene->Update();
	}
}

void SceneManager::Release()
{
	SAFE_DELETE(curScene);
	SAFE_DELETE(nextScene);
}
