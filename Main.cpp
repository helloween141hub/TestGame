#include <windows.h>
#include "GraphicsDevice.h"
#include "GameSprite.h"

//формируем функции по созданию окна
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y ,int width, int height, HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wPARAM, LPARAM lParam);


//Рисование и изменение
void Update(float gameTime);
void Draw(GraphicsDevice *device, float gametime);

GameSprite *player;
GameSprite *player2;


//основная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	if(GenerateWindow(hInstance, nCmdShow, "Direct3D", "Your first Win32 Window", 1280, 720, hWnd))
	{
		MSG msg;
		GraphicsDevice *gDevice = new GraphicsDevice();
		gDevice->Initialize(hWnd, true);

		player = new GameSprite(100,200);
		player2= new GameSprite(80,100);

		player->Initialize(gDevice->device, "PlayerPaper.png", 58,86);
		player2->Initialize(gDevice->device, "PlayerPaper.png", 58,86);
	

		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //проверяет есть ли в очереди сообщения и программа работает дальше(в отличиии от getMessage, которая ожидает пока не выолнися текущее событие(в духе синхронных и асинхронных процессов))
				{
					//PM_REMOVE - Удалять сообщения из очереди

					TranslateMessage(&msg); //преобразование клавиатурного ввода

					DispatchMessage(&msg);// обработка и пересылка сообщений в WindowProc
				}

				if(msg.message == WM_QUIT) break;
				else
				{
					//здесь будет прорисовка и обработка нажатий на клаву с мышью
					Update(0.0f);

					Draw(gDevice, 0.0f);
				}
		}

		delete player;
	    delete gDevice;

		return msg.wParam;
		
	}

	return 0;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, (GetSystemMetrics(SM_CXSCREEN) - width) / 2, 
		   (GetSystemMetrics(SM_CXSCREEN) - height)/2 , width, height, hWnd);
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className , LPCSTR windowTitle ,int x, int y, int width, int height, HWND& hWnd)
{
	
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}


	hWnd = CreateWindowEx(NULL, className, windowTitle,  WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 0,0, width, height, NULL, NULL, hInstance, NULL);

	//мутит полноэкранное окно
	//hWnd = CreateWindowEx(WS_EX_WINDOWEDGE , className, windowTitle, WS_VISIBLE, 0,0, GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CXSCREEN), NULL,NULL,hInstance, NULL);
	//SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & (~WS_CAPTION));
	// WS_VISIBLE - убирает верхнее меню окна

	ShowWindow(hWnd, nCmdShow);
	return true;
}


//обработчик события окна
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0); //ставит в очередь сообщение WM_destroy

			return 0;
		}
		break;

	case WM_PAINT:
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam); //обрабатывает те сообщения,которые вы не используете

}

void Update(float gameTime)
{
	//обновляем спрайты и другую игровую логику
	player->position.x++;
}



void Draw(GraphicsDevice *gDevice, float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));
	gDevice->Begin();

		player->Draw(gameTime);

		player2->Draw(gameTime);

	gDevice->End();
	gDevice->Present(); // Отобразить сцену
}
