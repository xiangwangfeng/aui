/**
 * @file    gdi_canvas.cpp
 * @brief   GDI画布
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#include "gdi_canvas.h"
#include "ui_macros.h"
#include "ui_resource_cache.h"
#include "ui_image.h"

GDICanvas::GDICanvas(HDC hdc,int width,int height)
:hdc_(hdc),
width_(width),
height_(height)
{
	assert(hdc);

	mem_hdc_	= CreateCompatibleDC(hdc_);
	bitmap_		= CreateCompatibleBitmap(hdc,width_,height_);
	old_bitmap_	= (HBITMAP)SelectObject(mem_hdc_,bitmap_);
	BitBlt(mem_hdc_,0,0,width_,height_,0,0,0,WHITENESS);
}

GDICanvas::~GDICanvas()
{
	BitBlt(hdc_,0,0,width_,height_,mem_hdc_,0,0,SRCCOPY);
	SelectObject(mem_hdc_,old_bitmap_);
	DeleteDC(mem_hdc_);
	DeleteObject(bitmap_);
}

void	GDICanvas::FillRect(const UIRect *rect,UIColor color)
{
	PTR_VOID(rect);
	HBRUSH brush = CreateSolidBrush(color);
	::FillRect(mem_hdc_,rect,brush);
	DeleteObject(brush);
}

void	GDICanvas::Rectangle(const UIRect *rect,UIColor color)
{
	PTR_VOID(rect);
	LOGBRUSH lb = {BS_NULL};
	HBRUSH brush = CreateBrushIndirect(&lb);
	HBRUSH old_brush = (HBRUSH)::SelectObject(mem_hdc_,brush);
	HPEN pen = CreatePen(PS_SOLID,1,color);
	HPEN old_pen = (HPEN)::SelectObject(mem_hdc_,pen);
	::Rectangle(mem_hdc_,rect->left,rect->top,rect->right,rect->bottom);
	::SelectObject(mem_hdc_,old_brush);
	::SelectObject(mem_hdc_,old_pen);
	::DeleteObject(brush);
	::DeleteObject(pen);
}

void	GDICanvas::SelectClipedRect(const UIRect *rect)
{
	PTR_VOID(rect);
	HRGN hrgn =  ::CreateRectRgnIndirect(rect);
	::SelectClipRgn(mem_hdc_,hrgn);
	DeleteObject(hrgn);
}

void	GDICanvas::DrawImage(const std::wstring &filepath,const UIRect *src,const UIRect *dst)
{
	UIImage *image = NULL;
	if (UIResourceCache::GetInstance()->GetImageByFilePath(filepath,&image))
	{
		image->Draw(mem_hdc_, dst, src);
	}
}

void	GDICanvas::DrawImage(const std::wstring &filepath,const UIRect *dst)
{
	UIImage *image = NULL;
	if (UIResourceCache::GetInstance()->GetImageByFilePath(filepath,&image))
	{
		image->Draw(mem_hdc_, dst);
	}
}

void	GDICanvas::DrawText(const wchar_t *text,size_t text_length,const UIRect *rect,UIColor text_color,UINT format,const UIFont *font /* = NULL */)
{
	HFONT old_font = NULL;
	HFONT current_font = NULL;
	if (font)
	{
		current_font = CreateFontIndirect(font);
		old_font = (HFONT)SelectObject(mem_hdc_,current_font);
	}


	SetBkMode(mem_hdc_,TRANSPARENT);
	UIColor old_text_color = ::SetTextColor(mem_hdc_,text_color);
	
	::DrawText(mem_hdc_,text,(int)text_length,&rect->ToRect(),format);

	if (old_font && current_font)
	{
		::SelectObject(mem_hdc_,old_font);
		::DeleteObject(current_font);
	}

	::SetTextColor(mem_hdc_,old_text_color);
}