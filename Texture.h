#pragma once

struct Texture
{
	string name;
	RECT r;
	LPDIRECT3DTEXTURE9 tex;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	list<shared_ptr<Texture>> textures;

public:
	TextureManager()
	{}
	virtual ~TextureManager()
	{}

public:
	shared_ptr<Texture> LoadTexture(const string& name)
	{
		for(auto tex : textures)
		{
			if(tex->name == name)
			{
				return tex;
			}
		}

		auto tex = new Texture();
		tex->name = name;
		D3DXIMAGE_INFO info;

		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device(),
			name.c_str(),
			D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
			1, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
			D3DX_FILTER_BOX, D3DX_FILTER_BOX,
			0,
			&info,
			nullptr,
			&tex->tex);

		SetRect(&tex->r, 0, 0, info.Width, info.Height);

		auto tmp = shared_ptr<Texture>(tex);
		textures.push_back(tmp);

		return tmp;
	}

	void Release()
	{
		for(auto tex : textures)
		{
			SAFE_RELEASE(tex->tex);
		}

		textures.clear();
	}
};

