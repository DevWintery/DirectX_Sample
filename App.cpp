#include"DXUT.h"
#include"Precompile.h"
#include"App.h"

App::App():
	screenSize(1920.f, 1080.f), sprite(nullptr), deltaTime(0.f), time(0)
{

}

App::~App()
{
}

void App::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
	cursor = ObjectList::GetInstance()->AddObject(new Sprite("Crosshair.png"));
	cursor->donDestory = true;
	cursor->isNonCamera = true;
	cursor->zOrder = 100;
}

void App::Update()
{
}

void App::DeviceReset()
{
	sprite->OnResetDevice();
}

void App::DeviceLost()
{
	sprite->OnLostDevice();
}

void App::Release()
{
	SAFE_RELEASE(sprite);
}
