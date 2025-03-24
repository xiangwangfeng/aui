/**
 * @file    gdi_image.h
 * @brief   GDI+ 图像封装类
 */
#pragma once
#include <windows.h>
#include <gdiplus.h>

class UIRect;

class GDIImage
{
public:
    GDIImage();
    ~GDIImage();

    // 从文件加载图像
    bool LoadFromFile(const wchar_t* file_path);
    // 获取图像宽度
    int GetWidth() const;
    // 获取图像高度
    int GetHeight() const;
    // 绘制图像
    bool Draw(HDC hdc, const UIRect* dst_rect, const UIRect* src_rect = nullptr);
    // 创建新图像
    bool Create(int width, int height);
    // 加载图像数据
    bool LoadFromMemory(const void* buffer, int size);

private:
    Gdiplus::Image* image_;
};