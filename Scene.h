#pragma once

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

public:
	shared_ptr<Camera> camera;

	virtual void Enter()
	{
		camera = ObjectList::GetInstance()->AddObject(new Camera());
	}
	virtual void Update() {}
	virtual void Exit()
	{
		ObjectList::GetInstance()->RemoveObject(camera);
	}
};

class SceneManager : public Singleton<SceneManager>
{
public:
	Scene* curScene;
	Scene* nextScene;

	SceneManager() :
		curScene(nullptr), nextScene(nullptr)
	{}
	virtual ~SceneManager() {}

public:
	void Start(Scene* startScene);

	void Change(Scene* newScene);

	void Update();

	void Release();
};