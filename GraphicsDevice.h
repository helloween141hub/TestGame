#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

//необходим длоя логики direct3d
#include <d3d9.h>

class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	//функции
	void Initialize(HWND hwnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();

	//указатель для интерфейса Iderect3DDevice *device
	LPDIRECT3DDEVICE9 device;
private:
	LPDIRECT3D9 direct3d;


};


#endif
