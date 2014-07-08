/**
 * @file    ui_label.h
 * @brief   UILabel
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-9
 * @website www.xiangwangfeng.com
 */

#pragma once
#include "ui_control.h"

struct	UILableConfig
{
	UILableConfig();
	std::wstring	text_;
	std::wstring	bk_image_;
	UIColor			text_color_;
	UIColor			text_link_color_;
	BOOL			is_hyperlink_;
	BOOL			is_single_line_;
	BOOL			always_show_underline_;
	std::wstring	url_;
	TextAlignment	hor_alignment_;
	TextAlignment	ver_alignment_;
	UIFont			font_;
};


class	UILabel : public UIControl
{
public:
	UILabel();

	void	SetText(const wchar_t *text);
	void	SetBkImage(const wchar_t *filepath);
	void	SetTextColor(UIColor color);
	void	SetTextLinkColor(UIColor color);
	void	SetURL(const wchar_t *url);
	void	SetAsHyperLink(BOOL is_hyperlink);
	void	SetSingleLine(BOOL is_single_line);
	void	SetShowUnderLine(BOOL show_underline);
	void	SetTextAlignment(TextAlignment hor_alignment,TextAlignment ver_alignment);
	void	SetTextFont(const UIFont &font);
	void	LoadConfig(const UILableConfig &config);
public:
	virtual	void	RenderSelf(const UIRect *rect);

	virtual	void	OnMouseEntered(UINT flag,const UIPoint &point);
	virtual	void	OnMouseExited(UINT flag,const UIPoint &point);
	virtual	BOOL	OnMouseMove(UINT flag,const UIPoint &point);
	virtual	BOOL	OnLButtonDown(UINT flag,const UIPoint &point);
	virtual BOOL	OnLButtonUp(UINT flag,const UIPoint &point);

private:
	void	OnClicked();

private:
	UILableConfig	config_;
	BOOL			is_mouse_in_;
	BOOL			self_clicked_;
};