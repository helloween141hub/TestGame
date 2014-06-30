#include "GameSprite.h"

GameSprite::GameSprite()
{
	//устанавливаем позиции по умолчанию
	position.x = 0;
	position.y = 0;
	position.z = 0;
	//УСТАНВАЛИВАЕМ БЕЛЫЙ ЦВЕТ
	color =D3DCOLOR_ARGB(255,255,255,255);
	//пока не инициализировали
	initialized = false;
}


GameSprite::GameSprite(float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	//пока не инициализировали
	initialized = false;
}

GameSprite::~GameSprite()
{
	if(sprite)
	{
		sprite->Release();
		sprite = 0;
	}

	if(tex)
	{
		tex->Release();
		tex = 0;
	}
}

bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, string file, int width, int height)
{
	
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(), width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, 
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex)))
	{
		string s = "There was an issue creating the texture/ Make sure the requested image is available. Requested image: "+file;
		MessageBox(NULL, s.c_str(), NULL, NULL);
	}

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "There was an issue creating the sprite", NULL, NULL);
		return false;
	}

	initialized = true;
	
	return true;
}


bool GameSprite::IsInitialized()
{
	return initialized;
}

void GameSprite::Update(float gameTime)
{

}

void GameSprite::Draw(float gameTime)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
		  sprite->Draw(tex, NULL, NULL, &position, color);
	sprite->End();
}

