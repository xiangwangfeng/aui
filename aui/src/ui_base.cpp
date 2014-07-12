/**
 * @file    ui_base.cpp
 * @brief   UI基础设施
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-5-2
 * @website www.xiangwangfeng.com
 */
#include "ui_base.h"

#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))

/////////////////////////////////////////////UIRect///////////////////////////////////////////////////////
UIRect::UIRect()
{
	left = top = right = bottom = 0;
}

UIRect::UIRect(const RECT& src)
{
	left = src.left;
	top = src.top;
	right = src.right;
	bottom = src.bottom;
}

UIRect::UIRect(int x,int y,int width,int height)
{
	left	= x;
	top		= y;
	right	= x + width;
	bottom	= y + height;
}

RECT	UIRect::ToRect() const
{
	RECT rect = *this;
	return rect;
}

int UIRect::GetX() const
{
	return left;
}

int UIRect::GetY() const
{
	return top;
}

int UIRect::GetWidth() const
{
	return right - left;
}

int UIRect::GetHeight() const
{
	return bottom - top;
}

void UIRect::Empty()
{
	left = top = right = bottom = 0;
}

void UIRect::Join(const RECT& rc)
{
	if( rc.left < left ) left = rc.left;
	if( rc.top < top ) top = rc.top;
	if( rc.right > right ) right = rc.right;
	if( rc.bottom > bottom ) bottom = rc.bottom;
}

void UIRect::ResetOffset()
{
	::OffsetRect(this, -left, -top);
}

void UIRect::Normalize()
{
	if( left > right ) { int iTemp = left; left = right; right = iTemp; }
	if( top > bottom ) { int iTemp = top; top = bottom; bottom = iTemp; }
}

void UIRect::Offset(int cx, int cy)
{
	::OffsetRect(this, cx, cy);
}

void UIRect::Inflate(int cx, int cy)
{
	::InflateRect(this, cx, cy);
}

void UIRect::Deflate(int cx, int cy)
{
	::InflateRect(this, -cx, -cy);
}

void UIRect::Union(UIRect& rc)
{
	::UnionRect(this, this, &rc);
}

UIRect	UIRect::IntersectRect(const UIRect *first,const UIRect *second)
{
	UIRect rect;
	::IntersectRect(&rect,first,second);
	return rect;
}


/////////////////////////////////////////UISize////////////////////////////////////////////////////
UISize::UISize()
{
   cx = cy = 0;
}

UISize::UISize(const SIZE &src)
{
   cx = src.cx;
   cy = src.cy;
}

UISize::UISize(const RECT &rc)
{
   cx = rc.right - rc.left;
   cy = rc.bottom - rc.top;
}

UISize::UISize(int _cx, int _cy)
{
   cx = _cx;
   cy = _cy;
}

////////////////////////////////////////UIPoint//////////////////////////////////////////
UIPoint::UIPoint()
{
   x = y = 0;
}

UIPoint::UIPoint(const POINT &src)
{
   x = src.x;
   y = src.y;
}

UIPoint::UIPoint(int _x, int _y)
{
   x = _x;
   y = _y;
}

UIPoint::UIPoint(LPARAM lParam)
{
   x = GET_X_LPARAM(lParam);
   y = GET_Y_LPARAM(lParam);
}


//////////////////////////////////////UIMargin////////////////////////////////////
UIMargin::UIMargin()
{
	left = top = right = bottom = 0;
}

UIMargin::UIMargin(int left_param,int top_param,int right_param,int bottom_param)
{
	left	= left_param;
	top		= top_param;
	right	= right_param;
	bottom	= bottom_param;
}