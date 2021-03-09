#pragma once

class Font : public Object
{
public:
	Font(int fontSize, const LPCWSTR& fontName, const wstring& text = L"");
	virtual ~Font();

private:
	LPD3DXFONT font;

public:
	wstring text;
	Color color = { 1, 1, 1, 1 };

public:
	virtual void Draw() override;
};