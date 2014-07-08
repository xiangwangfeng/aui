/**
 * @file    ui_button.h
 * @brief   UIButton
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-3
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <string>
#include "ui_control.h"

enum UIButtonStatus
{
	kUIButtonStatusNormal,
	kUIButtonStatusHover,
	kUIButtonStatusPressed,
	kUIButtonStatusDisable,
};

struct UIButtonConfig
{
	UIButtonConfig();
	
	std::wstring	button_text_;			
	std::wstring	normal_image_;			
	std::wstring	hover_image_;			
	std::wstring	pressed_image_;			
	std::wstring	disabled_image_;		
	UIColor			text_normal_color_;
	UIColor			text_focus_color_;
	UIColor			text_disable_color_;
	UIPoint			text_offset_;
	UIFont			font_;
	TextAlignment	text_alignment_;
};


class UIButton : public UIControl
{
public:
	UIButton();

	void	SetText(const wchar_t *text);
	void	SetNormalImage(const wchar_t *filepath);
	void	SetHoverImage(const wchar_t *filepath);
	void	SetPressedImage(const wchar_t *filepath);
	void	SetDisabledImage(const wchar_t *filepath);
	void	SetTextColor(UIColor color);
	void	SetFocusTextColor(UIColor color);
	void	SetDisableTextColor(UIColor color);
	void	SetTextOffset(const UIPoint &offset);
	void	SetTextAlignment(TextAlignment alignment);
	void	SetTextFont(const UIFont &font);
	void	LoadButtonConfig(const UIButtonConfig &config);

public:
	virtual	void	RenderSelf(const UIRect *rect);

	virtual	void	OnMouseEntered(UINT flag,const UIPoint &point);
	virtual	void	OnMouseExited(UINT flag,const UIPoint &point);
	virtual	BOOL	OnLButtonDown(UINT flag,const UIPoint &point);
	virtual BOOL	OnLButtonUp(UINT flag,const UIPoint &point);
private:
	void	SetButtonStatus(UIButtonStatus status);
	void	DrawText();
	void	OnClicked();
private:
	UIButtonStatus	button_status_;
	BOOL			self_clicked_;
	UIButtonConfig	config_;
};