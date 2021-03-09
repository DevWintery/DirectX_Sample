#include"DXUT.h"
#include"Precompile.h"
#include"ProgressBar.h"

ProgressBar::ProgressBar(const string & name) :
	Sprite(name), value(1.f), rect(texture->rect)
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Draw()
{
	Object::Draw();

	if (texture == nullptr) { return; }

	Vec3 center(texture->rect.right * 0.5f, texture->rect.bottom * 0.5f, 0);

	auto sprite = App::GetInstance()->sprite;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	auto tmp = GetTransform();
	sprite->SetTransform(&tmp);

	sprite->Draw(texture->texture, &rect, &center, nullptr, color);

	sprite->End();
}

void ProgressBar::Update()
{
	Sprite::Update();

	rect.right = texture->rect.right * value;
}

void ProgressBar::SetValue(float value)
{
	this->value = value;

	if (0.f > this->value)
	{
		this->value = 0.f;
	}

	if (this->value > 1.f)
	{
		this->value = 1.f;
	}
}