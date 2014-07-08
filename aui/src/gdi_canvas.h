/**
 * @file    gdi_canvas.h
 * @brief   GDI»­²¼
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <Windows.h>
#include "ui_canvas.h"

class CxImage;

class GDICanvas: public UICanvas
{
public:
	GDICanvas(HDC hdc,int width,int height);
	~GDICanvas();

public:
	virtual void	FillRect(const UIRect *rect,UIColor color);		//Ìî³ä¾ØÐÎ
	virtual	void	Rectangle(const UIRect *rect,UIColor color);	//»æÖÆ±ß¿ò
	virtual void	SelectClipedRect(const UIRect *rect);			//Ñ¡Ôñ²Ã¼ôÇøÓò
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *src,const UIRect *dst); //»æÖÆÍ¼Ïñ
	virtual void	DrawImage(const std::wstring &filepath,const UIRect *dst); //»æÖÆÍ¼Ïñ
	virtual	void	DrawText(const wchar_t *text,size_t text_length,const UIRect *rect,UIColor text_color,UINT format,const UIFont *font = NULL);//»æÖÆÎÄ×Ö
private:
	HDC	hdc_;			
	HDC mem_hdc_;		
	HBITMAP bitmap_;	
	HBITMAP old_bitmap_;
	int	width_;			
	int height_;
};
