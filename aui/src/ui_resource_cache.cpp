#include "ui_resource_cache.h"
#include "thirdparty/cximage/ximage.h"

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
	for (std::map<std::wstring,CxImage *>::iterator it = image_caches_.begin();
		it != image_caches_.end();it++)
	{
		delete it->second;
	}
}

BOOL	UIResourceCache::GetImageByFilePath(const std::wstring &filepath,CxImage **image)
{
	if (image_caches_.find(filepath) == image_caches_.end())
	{
		BOOL find = FALSE;
		CxImage *cximage = new CxImage();
		if (cximage->Load(filepath.c_str()))
		{
			image_caches_[filepath] = cximage;
			*image = cximage;
			find = TRUE;
		}
		else
		{
			delete image;
		}
		return find;
	}
	else
	{
		*image = image_caches_[filepath];
		return TRUE;
	}
}