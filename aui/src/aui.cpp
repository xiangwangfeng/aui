#include "aui.h"
#include "ui_resource_cache.h"

#ifdef _DEBUG
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#endif

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
	UIResourceCache::GetInstance();
}

void	CleanUpAUI()
{
	UIResourceCache::FreeInstance();
}