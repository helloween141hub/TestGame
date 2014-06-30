#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <d3dx9.h>
#include <string>
using namespace std;

class GameSprite
{
public:
	GameSprite();
	GameSprite(float x, float y);
	~GameSprite();

	bool Initialize(LPDIRECT3DDEVICE9 device, string file, int width, int height);
	bool IsInitialized();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);
public:
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	D3DXVECTOR3 position;
	D3DCOLOR color;
	bool initialized;

};


#endif
