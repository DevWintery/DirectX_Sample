#pragma once

struct Texture
{
	string name;
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	list<shared_ptr<Texture>> textures;

public:
	TextureManager();
	virtual ~TextureManager();

	shared_ptr<Texture> LoadTexture(const string& textureName);

	void Release();
};