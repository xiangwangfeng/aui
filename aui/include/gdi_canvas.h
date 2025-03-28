/**
 * @file    gdi_canvas.h
 * @brief   GDI画布
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <Windows.h>
#include "ui_canvas.h"

class UIImage;
class GDIImage;

class GDICanvas: public UICanvas
{
public:
	GDICanvas(HDC hdc,int width,int height);
	~GDICanvas();

public:
	virtual void	FillRect(const UIRect *rect,UIColor color);		//填充矩形
	virtual	void	Rectangle(const UIRect *rect,UIColor color);	//绘制边框
	virtual void	SelectClipedRect(const UIRect *rect);			//选择裁剪区域
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *src,const UIRect *dst); //绘制图像
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *dst); //绘制图像
	virtual void	DrawImage(UIImage *image,const UIRect *src,const UIRect *dst); //绘制图像
	virtual void	DrawImage(UIImage *image,const UIRect *dst); //绘制图像
	virtual	void	DrawText(const wchar_t *text,size_t text_length,const UIRect *rect,UIColor text_color,UINT format,const UIFont *font = NULL);//绘制文字

private:
	bool GDICanvas::DoDrawImage(UIImage*image,const UIRect *src,const UIRect *dst);
private:
	HDC	hdc_;			
	HDC mem_hdc_;		
	HBITMAP bitmap_;	
	HBITMAP old_bitmap_;
	int	width_;			
	int height_;
};
