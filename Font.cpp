#include"DXUT.h"
#include"Precompile.h"
#include"Font.h"

Font::Font(int fontSize, const LPCWSTR & fontName, const wstring & text) :
	Object(), text(text)
{
	D3DXCreateFont(DXUTGetD3D9Device(), fontSize, 0, FW_LIGHT, 1, TRUE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName, &font);
}

Font::~Font()
{
	SAFE_RELEASE(font);
}

void Font::Draw()
{
	Object::Draw();

	RECT rect;
	rect.left = position.x;
	rect.top = position.y;

	App::GetInstance()->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	font->DrawTextW(nullptr, text.c_str(), -1, &rect, DT_NOCLIP, color);

	App::GetInstance()->sprite->End();
}
