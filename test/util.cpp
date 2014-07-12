#include "util.h"
#include <Windows.h>

std::wstring	Util::GetAppPath()
{
	static std::wstring app_path;
	if (app_path.empty())
	{
		wchar_t	buffer[MAX_PATH];
		ZeroMemory(buffer, sizeof(wchar_t) * MAX_PATH);	
		::GetModuleFileName(NULL, buffer, MAX_PATH);
		std::wstring temp(buffer);
		size_t index = temp.rfind('\\');
		if (index == std::wstring::npos)
		{
			index = temp.rfind(';');
		}
		app_path = temp.substr(0,index + 1);
	}
	return app_path;
}