#pragma once
class Scene
{
public:
	Scene()
	{}
	virtual ~Scene()
	{}

public:
	shared_ptr<Camera> camera;

public:
	virtual void Enter()
	{
		camera = ObjectList::GetInstance()->AddObject(new Camera());
		camera->position = App::GetInstance()->screenSize * 0.5f;
	}

	virtual void Update()
	{
	}

	virtual void Exit()
	{
	}
};

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager():
		curScene(nullptr), nextScene(nullptr)
	{}

	virtual ~SceneManager()
	{}

public:
	Scene* curScene;
	Scene* nextScene;

public:
	void Start(Scene* scene)
	{
		curScene = scene;
		curScene->Enter();
	}

	void Change(Scene* scene)
	{
		nextScene = scene;
	}

	void Update()
	{
		if(nextScene != nullptr)
		{
			curScene->Exit();
			
			curScene = nextScene;
			nextScene = nullptr;
			
			ObjectList::GetInstance()->Release();

			curScene->Enter();
		}

		if(curScene != nullptr)
		{
			curScene->Update();
		}
	}

	void Release()
	{
		SAFE_DELETE(curScene);
		SAFE_DELETE(nextScene);
	}
};