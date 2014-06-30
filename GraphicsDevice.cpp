#include "GraphicsDevice.h"

GraphicsDevice::GraphicsDevice()
{

}

GraphicsDevice::~GraphicsDevice()
{
	if(device)
	{
		device->Release();
		device = NULL;
	}

	if(direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}


void GraphicsDevice::Initialize(HWND hWnd, bool windowed)
{
	//создаем указатель Direct 3d
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS presewntationParams;
	ZeroMemory(&presewntationParams, sizeof(presewntationParams));
	presewntationParams.Windowed = windowed;
	presewntationParams.SwapEffect =  D3DSWAPEFFECT_DISCARD;
	presewntationParams.hDeviceWindow = hWnd;


	//Создаем устройство
	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &presewntationParams, &device);

}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	//отображет сцену на экране
	device->Present(NULL, NULL, NULL, NULL);
}

