#include"DXUT.h"
#include"Precompile.h"
#include"Sprite.h"

Sprite::Sprite() :
	Object(), color(0xffffffff)
{
	
}

Sprite::Sprite(const string & name) :
	Object(), color(0xffffffff)
{
	texture = TextureManager::GetInstance()->LoadTexture(name);
}

Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	Object::Draw();

	if (texture == nullptr) { return; }

	anchorPoint = Vec3(texture->rect.right, texture->rect.bottom, 0.f);
	anchorPoint *= 0.5f;

	auto sprite = App::GetInstance()->sprite;

	if (isNonCamera)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	}

	auto tmp = GetTransform();
	sprite->SetTransform(&tmp);

	sprite->Draw(texture->texture, nullptr, &anchorPoint, nullptr, color);

	sprite->End();
}

RECT& Sprite::GetRect() 
{
	return Rect::TextureRectToSpriteRect(this);
}

