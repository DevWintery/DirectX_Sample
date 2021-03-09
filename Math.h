#pragma once

namespace Rect
{
	inline RECT TextureRectToSpriteRect(const Sprite* spr)
	{
		RECT r;
		RECT rect = spr->texture->rect;
		auto scale = spr->scale;
		auto pos = spr->position;

		r.left = static_cast<long>(pos.x - (rect.right / 2) * scale.x);
		r.right = static_cast<long>(pos.x + (rect.right / 2) * scale.x);
		r.top = static_cast<long>(pos.y - (rect.bottom / 2) * scale.y);
		r.bottom = static_cast<long>(pos.y + (rect.bottom / 2) * scale.y);

		return r;
	}

	inline bool CollisionPoint(const RECT& rect, const Vec2& point)
	{
		if (rect.left <= point.x && rect.right >= point.x && rect.top <= point.y && rect.bottom >= point.y)
		{
			return true;
		}

		return false;
	}

	inline bool CollisionRect(const RECT& r1, const RECT& r2)
	{
		if (r1.left <= r2.right && r1.right >= r2.left && r1.top <= r2.bottom && r1.bottom >= r2.top)
		{
			return true;
		}

		return false;
	}
}

namespace Math
{
	inline Vec2 RotateVector2(const Vec2& vector, float rotation)
	{
		float _rotation = D3DXToRadian(rotation);
		Vec2 tmp;

		tmp.x = vector.x * cosf(_rotation) - vector.y * sinf(_rotation);
		tmp.y = vector.x * sinf(_rotation) + vector.y * cosf(_rotation);

		return tmp;
	}
};
