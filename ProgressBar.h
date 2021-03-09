#pragma once

class ProgressBar : public Object
{
public:
	ProgressBar(const string& name):
		Object(), color(0xffffffff), value(1.f)
	{
		tex = TextureManager::GetInstance()->LoadTexture(name);
		rect = tex->r;
	}
	virtual ~ProgressBar()
	{}

public:
	shared_ptr<Texture> tex;
	Color color;
	RECT rect;
	float value;

public:
	virtual void Draw()
	{
		Object::Draw();

		Vec3 center = Vec3(tex->r.right, tex->r.bottom, 0.f);
		center *= 0.5f;

		auto spr = App::GetInstance()->spr;

		if(isNonCamera)
		{
			spr->Begin(D3DXSPRITE_ALPHABLEND);
		}
		else
		{
			spr->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		}
		auto transform = GetTransform();
		spr->SetTransform(&transform);

		spr->Draw(tex->tex, &rect, &center, nullptr, color);

		spr->End();
	}

	virtual void Update()
	{
		Object::Update();

		rect.right = tex->r.right * value;
	}

	void SetValue(float _value)
	{
		value = _value;
		
		if(0.f > value)
		{
			value = 0.f;
		}

		if(value > 1.f)
		{
			value = 1.f;
		}
	}
};

