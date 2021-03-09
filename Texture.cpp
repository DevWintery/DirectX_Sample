#include"DXUT.h"
#include"Precompile.h"
#include"Texture.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

shared_ptr<Texture> TextureManager::LoadTexture(const string & textureName)
{
	for(auto texture : textures)
	{
		if(texture->name == textureName)
		{
			return texture;
		}
	}

	Texture* newTexture = new Texture();
	newTexture->name = textureName;
	D3DXIMAGE_INFO imageInfo;

	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device(),
		textureName.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0,
		D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE,
		0,
		&imageInfo,
		nullptr,
		&newTexture->texture);

	SetRect(&newTexture->rect, 0, 0, imageInfo.Width, imageInfo.Height);
	
	shared_ptr<Texture> tmp = shared_ptr<Texture>(newTexture);
	textures.push_back(tmp);

	return tmp;
}

void TextureManager::Release()
{
	for(auto texture : textures)
	{
		SAFE_RELEASE(texture->texture);
	}

	textures.clear();
}
