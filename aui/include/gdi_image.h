/**
 * @file    gdi_image.h
 * @brief   GDI+ 图像封装类
 */
#pragma once
#include <windows.h>
#include <gdiplus.h>
#include "ui_image.h"

class UIRect;

class GDIImage : public UIImage
{
public:
    GDIImage();
    virtual ~GDIImage();

    virtual bool LoadFromFile(const wchar_t* file_path) override;

    virtual int GetWidth() const override;

    virtual int GetHeight() const override;

    Gdiplus::Image* GetImage() const {return image_;}

private:
    Gdiplus::Image* image_;
};