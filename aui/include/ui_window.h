/**
 * @file    ui_window.h
 * @brief   通用窗口类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <vector>
#include "native_window.h"
#include "ui_base.h"


class UICanvas;
class UIControl;
class IUINotify;

class UIWindow : public NativeWindow
{
public:
	UIWindow();
	~UIWindow();
	//消息循环
	virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
	//添加根控件
	void	AddRootControl(UIControl *root_control);
	//对控件进行排版
	void	UpdateLayout();
	//刷新界面
	void	Invalidate(const UIRect *rect);
	//设置窗口最大最小值
	void	SetWindowMinSize(const UISize *size);
	void	SetWindowMinSize(int width,int height);
	void	SetWindowMaxSize(const UISize *size);
	void	SetWindowMaxSize(int width,int height);
	//添加观察者
	void	AddNotifier(IUINotify *notifier);
	void	FireEvent(UINotifyEvent event,UIControl *contorl);
	//继承自NativeWindow的方法
	virtual void	OnSize(UINT type,int cx,int cy);
	virtual void	OnGetMinMaxInfo(MINMAXINFO* lpMMI);
private:
	//绘制方法
	void	Render(const UIRect *rect);
	//实际排版方法
	void	DoUpdateLayout();
	//处理WM_PAINT
	void	HandleWMPaintMessage();
	//处理鼠标消息
	void	HandleMouseMessage(UINT message,WPARAM wParam,LPARAM lParam);
	//设置当前鼠标
	void	SetCurrentMouseControl(UIControl *control);
private:
	BOOL		is_closing_;			//正在关闭
	BOOL		resize_needed_;			//需要重排版
	BOOL		is_mouse_in_;			//鼠标是否在窗口内
	UIControl	*current_mouse_control_;//当前鼠标焦点控件
	UIControl	*root_control_;			//根节点
	UISize		min_size_;				//窗口最小大小
	UISize		max_size_;				//窗口最大大小
	std::vector<IUINotify *>	notifiers;
};