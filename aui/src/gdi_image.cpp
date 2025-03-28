/**
 * @file    gdi_image.cpp
 * @brief   GDI+ 图像封装类
 */
#include "gdi_image.h"
#include "ui_base.h"

GDIImage::GDIImage()
    : image_(nullptr)
{
}

GDIImage::~GDIImage()
{
    if (image_)
    {
        delete image_;
        image_ = nullptr;
    }
}

bool GDIImage::LoadFromFile(const wchar_t* file_path)
{
    if (!file_path)
    {
        return false;
    }

    if (image_)
    {
        delete image_;
        image_ = nullptr;
    }

    image_ = Gdiplus::Image::FromFile(file_path);
    return image_ != nullptr && image_->GetLastStatus() == Gdiplus::Ok;
}

int GDIImage::GetWidth() const
{
    return image_ ? image_->GetWidth() : 0;
}

int GDIImage::GetHeight() const
{
    return image_ ? image_->GetHeight() : 0;
}


