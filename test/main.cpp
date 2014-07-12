#include <Windows.h>
#include "main_window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{

	InitAUI();

	MainWindow window;
	if (window.Create(NULL,L"毛的主窗口",WS_OVERLAPPEDWINDOW | WS_VISIBLE,0,CW_USEDEFAULT,CW_USEDEFAULT,300,350))
	{
		window.SetWindowMinSize(300,350);
		window.SetAsMainWindow();
		window.CenterWindow();
		window.ShowWindow();
	}



	MSG msg;
	BOOL bRet;

	while((bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			break;
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	CleanUpAUI();

	return 0;
}