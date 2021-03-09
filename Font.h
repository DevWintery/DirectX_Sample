#pragma once

class Font : public Object
{
public:
	Font(int fontSize, const LPCWSTR& fontName, const wstring& text);
	virtual ~Font();

public:
	Color color = { 1.f, 1.f, 1.f, 1.f};
	wstring text;
	LPD3DXFONT font;

public:
	virtual void Draw() override;
};