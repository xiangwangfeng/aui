/**
 * @file    ui_resource_manager.h
 * @brief   UI资源缓存
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-6-28
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <string>
#include <map>
#include <Windows.h>
class CxImage;

class UIResourceCache
{
public:
	~UIResourceCache();
	static UIResourceCache* GetInstance();
	static void FreeInstance();
	static UIResourceCache *cache_;

	BOOL GetImageByFilePath(const std::wstring &filepath,CxImage **image);
private:
	UIResourceCache();
private:
	std::map<std::wstring,CxImage *> image_caches_;
};