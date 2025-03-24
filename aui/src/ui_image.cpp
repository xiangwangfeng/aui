/**
 * @file    ui_image.cpp
 * @brief   图像封装类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 */
#include "ui_image.h"
#include "ui_base.h"

UIImage::UIImage()
    : image_(nullptr)
{
}

UIImage::~UIImage()
{
    if (image_)
    {
        delete image_;
        image_ = nullptr;
    }
}

bool UIImage::LoadFromFile(const wchar_t* file_path)
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

int UIImage::GetWidth() const
{
    return image_ ? image_->GetWidth() : 0;
}

int UIImage::GetHeight() const
{
    return image_ ? image_->GetHeight() : 0;
}

bool UIImage::Draw(HDC hdc, const UIRect* dst_rect, const UIRect* src_rect)
{
    if (!image_ || !hdc || !dst_rect)
    {
        return false;
    }

    Gdiplus::Graphics graphics(hdc);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

    Gdiplus::RectF dest_rect(
        static_cast<Gdiplus::REAL>(dst_rect->left),
        static_cast<Gdiplus::REAL>(dst_rect->top),
        static_cast<Gdiplus::REAL>(dst_rect->right - dst_rect->left),
        static_cast<Gdiplus::REAL>(dst_rect->bottom - dst_rect->top));

    if (src_rect)
    {
        return graphics.DrawImage(image_, dest_rect,
            static_cast<Gdiplus::REAL>(src_rect->left),
            static_cast<Gdiplus::REAL>(src_rect->top),
            static_cast<Gdiplus::REAL>(src_rect->right - src_rect->left),
            static_cast<Gdiplus::REAL>(src_rect->bottom - src_rect->top),
            Gdiplus::UnitPixel) == Gdiplus::Ok;
    }
    else
    {
        return graphics.DrawImage(image_, dest_rect) == Gdiplus::Ok;
    }
}

bool UIImage::Create(int width, int height)
{
    if (image_)
    {
        delete image_;
        image_ = nullptr;
    }

    image_ = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
    return image_ != nullptr && image_->GetLastStatus() == Gdiplus::Ok;
}

bool UIImage::LoadFromMemory(const void* buffer, int size)
{
    if (!buffer || size <= 0)
    {
        return false;
    }

    if (image_)
    {
        delete image_;
        image_ = nullptr;
    }

    IStream* stream = nullptr;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size);
    if (hMem)
    {
        void* pMem = GlobalLock(hMem);
        if (pMem)
        {
            memcpy(pMem, buffer, size);
            GlobalUnlock(hMem);
            if (CreateStreamOnHGlobal(hMem, TRUE, &stream) == S_OK)
            {
                image_ = Gdiplus::Image::FromStream(stream);
                stream->Release();
            }
        }
        GlobalFree(hMem);
    }

    return image_ != nullptr && image_->GetLastStatus() == Gdiplus::Ok;
}
