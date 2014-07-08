/**
 * @file    ui_base.h
 * @brief   UI基础设施
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-5-2
 * @website www.xiangwangfeng.com
 */

#pragma once
#include<Windows.h>

//UIRect
class UIRect : public tagRECT
{
public:
	UIRect();
	UIRect(const RECT& src);
	UIRect(int x,int y,int width,int height);

	RECT ToRect() const;
	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
	void Empty();
	void Join(const RECT& rc);
	void ResetOffset();
	void Normalize();
	void Offset(int cx, int cy);
	void Inflate(int cx, int cy);
	void Deflate(int cx, int cy);
	void Union(UIRect& rc);

	static UIRect IntersectRect(const UIRect *first,const UIRect *second);
};


//UISize
class UISize : public tagSIZE
{
public:
   UISize();
   UISize(const SIZE &src);
   UISize(const RECT &rc);
   UISize(int cx, int cy);
};


//UIPoint
class  UIPoint : public tagPOINT
{
public:
   UIPoint();
   UIPoint(const POINT &src);
   UIPoint(int x, int y);
   UIPoint(LPARAM lParam);
};


typedef COLORREF UIColor;
typedef LOGFONT	 UIFont;

struct UIMargin 
{
	UIMargin();
	UIMargin(int left,int top = 0,int right = 0,int bottom = 0);

	int left;
	int top;
	int right;
	int bottom;
};

enum TextAlignment
{
	kTextAlignmentLeft		= DT_LEFT,
	kTextAlignmentCenter	= DT_CENTER,
	kTextAlignmentRight		= DT_RIGHT,

	kTextAlignmentTop		= DT_TOP,
	kTextAlignmentVCenter	= DT_VCENTER,
	kTextAlignmentBottom	= DT_BOTTOM,
};

class UIControl;
enum UINotifyEvent
{
	kEventClick,		//点击事件
	kEventTextChanged,	//文本变化事件
};

class IUINotify
{
public:
	virtual	void Notify(UINotifyEvent event,UIControl *control) = 0;
};
