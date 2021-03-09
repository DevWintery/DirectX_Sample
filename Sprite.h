#pragma once

class Sprite : public Object
{
public:
	shared_ptr<Texture> texture;
	Color color;
	Vec3 anchorPoint;

public:
	Sprite();
	Sprite(const string& name);
	virtual ~Sprite();

	virtual void Draw() override;
	virtual void Update() override
	{
		Object::Update();

		if(texture != nullptr)
		{
			Vec2 size((texture->rect.right - texture->rect.left) * scale.x, (texture->rect.bottom - texture->rect.top) * scale.y);
			obb = OBB2D(position, size.x, size.y, rotation);
		}
	}
public:
	RECT& GetRect();
	OBB2D obb;
};