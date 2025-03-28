/**
 * @file    ui_image.h
 * @brief   图像封装类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 */
#pragma once
#include <windows.h>
#include <gdiplus.h>

class UICanvas;
class UIRect;
class UIImage
{
    public:
        virtual ~UIImage() {}

        // 从文件加载图像
        virtual bool LoadFromFile(const wchar_t* file_path) = 0;
        // 获取图像宽度
        virtual int GetWidth() const = 0;
        // 获取图像高度
        virtual int GetHeight() const = 0;
};