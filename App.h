#pragma once

class App : public Singleton<App>
{
public:
	App():
		screenSize(1920.f, 1080.f), mouseClick(false), alreadyMouseClick(false), spr(nullptr), deltaTime(0.f), time(0), sound(nullptr)
	{}
	virtual ~App()
	{}

public:
	Vec2 screenSize;

	Vec2 mousePosition;
	bool mouseClick;
	bool alreadyMouseClick;

	LPD3DXSPRITE spr;
	CSoundManager* sound;

	float deltaTime;
	double time;

public:
	void Init()
	{
		sound = new CSoundManager();

		D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
		sound->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
		sound->SetPrimaryBufferFormat(2, 22050, 16);
	}

	void PlayHochi()
	{
		CSound* hochi;
		sound->Create(&hochi, L"Resources/Sound/Hochi.wav", 0, GUID_NULL);	
		hochi->Play(0, NULL);
	}

	void PlayPew()
	{
		CSound* hochi;
		HRESULT hr = sound->Create(&hochi, L"Resources/Sound/Bu.wav", 0, GUID_NULL);
		
		hochi->Play(0, NULL);
	}

	void DeviceReset()
	{
		spr->OnResetDevice();
	}

	void DeviceLost()
	{
		spr->OnLostDevice();
	}

	void Release()
	{
		SAFE_DELETE(sound);
		SAFE_RELEASE(spr);
	}
};

