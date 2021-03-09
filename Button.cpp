#include"DXUT.h"
#include"Precompile.h"
#include"Button.h"

Button::Button(const string& name, function<void()> fuc):
	Sprite(name), alreadyMouseClick(false)
{
	isNonCamera = true;
	normalTexture = TextureManager::GetInstance()->LoadTexture(name);
	this->fuc = fuc;
}

void Button::Update()
{
	Sprite::Update();

	if(Rect::CollisionPoint(GetRect(), App::GetInstance()->mousePosition))
	{
		if (highlightTexture != nullptr) 
		{
			texture = highlightTexture;
		}

		if (!alreadyMouseClick && App::GetInstance()->leftDown && !App::GetInstance()->alreadyLeftDown)
		{
			alreadyMouseClick = true;
			if(pushTexture != nullptr) { texture = pushTexture; }
		}

		if (alreadyMouseClick && !App::GetInstance()->leftDown)
		{
			alreadyMouseClick = false;
			texture = normalTexture;
			fuc();
		}
	}
	else
	{
		texture = normalTexture;
	}
}
