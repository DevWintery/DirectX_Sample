#include "DXUT.h"
#include"Precompile.h"
#include "Sprite.h"

RECT Sprite::GetRect()
{
	return Rect::Tex2SprTex(this);
}
