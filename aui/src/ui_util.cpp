/**
 * @file    ui_util.cpp
 * @brief   UI¸¨Öú·½·¨
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-7
 * @website www.xiangwangfeng.com
 */
#include "ui_util.h"
#include <Windows.h>

namespace AUI{

std::wstring	UTF8toUTF16(const char *source)
{
	int length = ::MultiByteToWideChar(CP_UTF8, 0, source, -1, NULL, 0);
	wchar_t *dst = new wchar_t[length];
	::MultiByteToWideChar(CP_UTF8, 0, source, -1, dst, length);
	std::wstring output(dst,length);
	delete []dst;
	return output;
}

void	GetDefaultUIFont(UIFont& font)
{
	memset(&font, 0, sizeof(UIFont));
	font.lfHeight				= -11;
	font.lfWeight				= FW_NORMAL;
	font.lfOutPrecision			= OUT_STROKE_PRECIS;
	font.lfClipPrecision		= CLIP_STROKE_PRECIS;
	font.lfQuality			=	 DEFAULT_QUALITY;
	font.lfPitchAndFamily		= VARIABLE_PITCH | FF_SWISS;
	wcscpy_s(font.lfFaceName, L"SimSum");
}

UIFont *GetGlobalEditFont()
{
	static UIFont *global_font = NULL;
	if (global_font == NULL)
	{
		global_font = new UIFont();
		memset(global_font, 0, sizeof(UIFont));
		global_font->lfHeight				= -15;
		global_font->lfWeight				= FW_NORMAL;
		global_font->lfOutPrecision			= OUT_STROKE_PRECIS;
		global_font->lfClipPrecision		= CLIP_STROKE_PRECIS;
		global_font->lfQuality				= DEFAULT_QUALITY;
		global_font->lfPitchAndFamily		= VARIABLE_PITCH | FF_SWISS;
		wcscpy_s(global_font->lfFaceName, L"SimSum");
	}
	return global_font;
}

void	SafeOpenURL(const wchar_t *url,int flag,BOOL use_default_browser)
{
	if (use_default_browser)
	{
		::ShellExecute(NULL,L"open",url,NULL,NULL,flag);
	}
	else
	{
		::ShellExecute(NULL,L"open",L"IEEXPLORE.EXE",url,NULL,flag);
	}
}


};