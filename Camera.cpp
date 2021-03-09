#include"DXUT.h"
#include"Precompile.h"
#include"Camera.h"

Camera::Camera() :
	Object(), shaking(false)
{
	D3DXMatrixOrthoLH(&orthographicMatrix, App::GetInstance()->screenSize.x, -App::GetInstance()->screenSize.y, 0.f, 1.f);
	D3DXMatrixIdentity(&identityMatrix);

	position = App::GetInstance()->screenSize * 0.5f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Object::Update();

	viewMatrix = Matrix4(
		scale.x * cos(rotation), scale.x * sin(rotation), 0.f, 0.f,
		-scale.y * sin(rotation), scale.y * cos(rotation), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		-position.x * scale.x * cos(rotation) + position.y * scale.y * sin(rotation),
		-position.x * scale.y * sin(rotation) - position.y * scale.y * cos(rotation), 0.f, 1.f);

	if(shaking)
	{
		Shake();
	}
}

void Camera::Draw()
{
	Object::Draw();

	SetTransform();
}


void Camera::SetTransform()
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, &identityMatrix);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::Shake()
{
	shaking = true;

	position += Vec2(rand() % 100 - 50, rand() % 100 - 50);

	timers.push_back(Timer([&]()
	{
		shaking = false;
	}
		, 0.1f));
}
