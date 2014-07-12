/**
 * @file    ui_canvas.h
 * @brief   画布接口定义类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <string>
#include "ui_base.h"



class	UICanvas
{
public:;
	virtual void	FillRect(const UIRect *rect,UIColor color) = 0;
	virtual	void	Rectangle(const UIRect *rect,UIColor color) = 0;
	virtual void	SelectClipedRect(const UIRect *rect) = 0;
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *src,const UIRect *dst) = 0;
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *dst) = 0;
	virtual	void	DrawText(const wchar_t *text,size_t text_length,const UIRect *rect,UIColor text_color,UINT format,const UIFont *font = NULL) = 0;
};

UICanvas *CurrentCanvas();
void	SetCurrentCanvas(UICanvas *canvas);