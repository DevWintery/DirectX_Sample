#pragma once

class Sprite;

class App : public Singleton<App>
{
public:
	App();
	virtual ~App();

public:
	Vec2 screenSize;
	LPD3DXSPRITE sprite;
	
	Vec2 mousePosition;
	bool leftDown;
	bool alreadyLeftDown;

	shared_ptr<Sprite> cursor;

	float deltaTime;
	double time;

public:
	void Init();

	void Update();

	void DeviceReset();
	void DeviceLost();
	void Release();
};