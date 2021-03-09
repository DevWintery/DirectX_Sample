#pragma once

namespace Rect
{
	inline RECT Tex2SprTex(Sprite* spr)
	{
		RECT r;
		Vec2 pos = spr->position;
		Vec2 scale = spr->scale;
		RECT rect = spr->tex->r;

		r.left = pos.x - (rect.right / 2) * scale.x;
		r.right = pos.x + (rect.right / 2) * scale.x;
		r.top = pos.y - (rect.bottom / 2) * scale.y;
		r.bottom = pos.y + (rect.bottom / 2) * scale.y;

		return r;
	}

	inline bool CollisionPoint(const RECT& r, const Vec2& pos)
	{
		if(pos.y >= r.top && pos.y <= r.bottom && pos.x >= r.left && pos.x <= r.right)
		{
			return true;
		}

		return false;
	}

	inline bool CollisionRect(const RECT& r1, const RECT& r2)
	{
		if(r1.bottom >= r2.top && r1.top <= r2.bottom && r1.right >= r2.left && r1.left <= r2.right)
		{
			return true;
		}

		return false;
	}
}