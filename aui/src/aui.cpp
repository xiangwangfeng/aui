#include "aui.h"
#include "ui_resource_cache.h"

#ifdef _DEBUG
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#endif

static ULONG_PTR g_gdiplusToken = 0;

void	InitAUI()
{
	/*
#ifdef _DEBUG
	int nCrt = 0;
	FILE* fp;
	AllocConsole();
	nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(nCrt, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

#endif
	*/

	// 初始化 GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL);

	UIResourceCache::GetInstance();
}

void	CleanUpAUI()
{
	UIResourceCache::FreeInstance();

	// 关闭 GDI+
	if (g_gdiplusToken != 0)
	{
		Gdiplus::GdiplusShutdown(g_gdiplusToken);
		g_gdiplusToken = 0;
	}
}