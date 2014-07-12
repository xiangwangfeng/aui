/**
 * @file    ui_control.h
 * @brief   UI控件基类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */
#pragma once
#include <string>
#include <vector>
#include "ui_base.h"

//定位方式
enum Alignment
{
//绝对定位
	kAlignmentLeftTop,
	kAlignmentLeftCenter,
	kAlignmentLeftBottom,
	kAlignmentCenterTop,
	kAlignmentCenter,
	kAlignmentCenterBottom,
	kAlignmentRightTop,
	kAlignmentRightCenter,
	kAlignmentRightBottom,
//相对定位
	kAlignmentLeft,
	kAlignmentRight,
	kAlignmentTop,
	kAlignmentBottom,
	kAlignmentFill,
};

class UICanvas;
class UIWindow;
class UIControl;



class UIControl
{
public:
	UIControl();
	virtual ~UIControl();
	void	SetAttribute(const char *name,const char *value);
public:
	//控件名
	void			SetControlName(const char *name);
	std::string		GetControlName() const;
	//Tag值
	void		SetTag(int tag);
	int			GetTag() const;
	//控件外边距
	void		SetMargin(const UIMargin &margin);
	void		SetMargin(int left,int top = 0,int right = 0,int bottom = 0);
	//控件大小
	void		SetSize(const UISize &size);
	void		SetSize(int width,int height);
	UISize		GetSize() const;
	//控件定位方式
	void		SetAlignmentType(Alignment type);
	Alignment	GetAlignmentType() const;
	//控件可见性
	void		SetVisible(BOOL visible);
	BOOL		IsVisible() const;
	//控件可用性
	void		SetEnabled(BOOL enabled);
	BOOL		IsEnabled() const;
	//父控件
	void		SetParent(UIControl *control);
	UIControl*	GetParent() const;
	//添加/移除子控件
	void		AddSubControl(UIControl *control);
	void		RemoveSubControl(const std::string &name);
	//绘制
	virtual	void	RenderSelf(const UIRect *rect);
	//重排版
	virtual	void	ArrangeSelf(const UIRect *parent_frame);
	//查找
	UIControl*	LookupMouseFocusedControl(const UIPoint &point);
	//设置frame
	void		SetRootFrame(const UIRect *rect);
	void		SetFrame(const UIRect *rect);
	UIRect		GetFrame() const;
	//设置父窗口
	void	SetParentWin(UIWindow *window);
	UIWindow*	GetParentWin(); 
	//设置需要绘制和设置需要从排版
	void	SetNeedDisplay();
	void	SetNeedLayout();
	//设置光标状态
	void	SetCursor(const wchar_t *cursor_name);
	//鼠标消息
	virtual	BOOL	OnMouseMessage(UINT message,WPARAM wParam,LPARAM lParam);
	virtual	void	OnMouseEntered(UINT flag,const UIPoint &point);
	virtual	void	OnMouseExited(UINT flag,const UIPoint &point);
	//鼠标左键消息
	virtual	BOOL	OnLButtonDown(UINT flag,const UIPoint &point);
	virtual	BOOL	OnLButtonUp(UINT flag,const UIPoint &point);
	virtual	BOOL	OnLButtonDoubleClicked(UINT flag,const UIPoint &point);
	//鼠标右键消息
	virtual	BOOL	OnRButtonDown(UINT flag,const UIPoint &point);
	virtual	BOOL	OnRButtonUp(UINT flag,const UIPoint &point);
	virtual	BOOL	OnRButtonDoubleClicked(UINT flag,const UIPoint &point);
	//鼠标中键消息
	virtual	BOOL	OnMButtonDown(UINT flag,const UIPoint &point);
	virtual	BOOL	OnMButtonUp(UINT flag,const UIPoint &point);
	virtual	BOOL	OnMButtonDoubleClicked(UINT flag,const UIPoint &point);
	//鼠标滚轮
	virtual void	OnMouseWheel(UINT flag, short delta,const UIPoint &point);
	//鼠标移动
	virtual	BOOL	OnMouseMove(UINT flag,const UIPoint &point);
protected:
	//发送通知事件
	void	SendNotify(UINotifyEvent event);
private:
	//绘制
	void	Render(const UIRect *parent_rect);
	//重排版;
	void	Arrange(const UIRect *parent_frame);
	void	ArrangeChildren(const UIRect *parent_frame);
	//设置递归设置子控件的父亲可见性和可用性
	void	SetParentVisibleRecursive(BOOL visible);
	void	SetParentEnabledRecursive(BOOL enabled);
	//是否在当前控件内
	BOOL		IsMouseInControl(const UIPoint &point);
	//派发鼠标消息
	void		DispatchMouseMessage(UINT message,WPARAM wParam,LPARAM lParam);
	//通过属性返回Alignment
	Alignment	GetAlignmentByString(const char *value);
protected:
	std::vector<UIControl *>	children_;		//子控件
	UISize						size_;			//控件大小
	Alignment					alignment_type_;//定位方式
	UIMargin					margin_;		//外边距
	UIRect						frame_;			//在窗口上的绝对位置
	UIControl					*parent_;		//父控件
	UIWindow					*parent_win_;	//父窗口
	std::string					name_;			//控件名
	int							tag_;			//tag值
	BOOL						visible_;		//是否可见
	BOOL						parent_visible_;//父亲是否可见
	BOOL						enabled_;		//是否可用
	BOOL						parent_enabled_;//父亲是否可用
	
	friend	UIControl;
	friend	UIWindow;
};