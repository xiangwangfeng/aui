#include "ui_resource_cache.h"
#include "gdi_image.h"

UIResourceCache* UIResourceCache::cache_ = NULL;

UIResourceCache*	UIResourceCache::GetInstance()
{
	if (cache_ == NULL)
	{
		cache_ = new UIResourceCache();
	}
	return cache_;
}

void	UIResourceCache::FreeInstance()
{
	delete cache_;
}

UIResourceCache::UIResourceCache()
{

}

UIResourceCache::~UIResourceCache()
{
	for (std::map<std::wstring, UIImage*>::iterator it = image_caches_.begin();
		it != image_caches_.end(); it++)
	{
		delete it->second;
	}
}

BOOL	UIResourceCache::GetImageByFilePath(const std::wstring &filepath, UIImage** image)
{
	if (image_caches_.find(filepath) == image_caches_.end())
	{
		BOOL find = FALSE;
		GDIImage* uiimage = new GDIImage();
		if (uiimage->LoadFromFile(filepath.c_str()))
		{
			image_caches_[filepath] = uiimage;
			*image = uiimage;
			find = TRUE;
		}
		else
		{
			delete uiimage;
		}
		return find;
	}
	else
	{
		*image = image_caches_[filepath];
		return TRUE;
	}
}