/**
 * @file    ui_panel.h
 * @brief   UIPanel
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-6-20
 * @website www.xiangwangfeng.com
 */
#pragma once
#include "ui_control.h"

class UIPanel : public UIControl
{
public:	
	//背景色
	void	SetBKColor(UIColor color);
	//背景图片
	void	SetBKImage(const std::wstring &filepath);
public:
	virtual	void	RenderSelf(const UIRect *rect);

private:
	UIColor			bk_color_;
	std::wstring	bk_filepath_;
};
