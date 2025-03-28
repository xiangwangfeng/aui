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

static RenderBackend s_currentRenderBackend = RenderBackend::GDIPlus;

void SetRenderBackend(RenderBackend backend) {
    s_currentRenderBackend = backend;
}

RenderBackend GetCurrentRenderBackend() {
    return s_currentRenderBackend;
}