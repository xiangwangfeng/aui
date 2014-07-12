/**
 * @file    ui_edit.h
 * @brief   UIEdit
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-11
 * @website www.xiangwangfeng.com
 */
#pragma once
#include "ui_control.h"
#include "native_window.h"

struct UIEditConfig
{
	UIEditConfig();
	UIColor			border_color_;
	UIColor			text_color_;
	BOOL			is_password_edit_;
	std::wstring	text_;
};

class UIEditWindow;
class UIEdit : public UIControl
{
public:
	UIEdit();

	const wchar_t *GetEditText() const;
	void	SetEditText(const wchar_t *text,BOOL redraw =FALSE);

	void	SetBorderColor(UIColor color);
	void	SetTextColor(UIColor color);
	void	SetAsPasswordEdit(BOOL is_password_edit);
	void	LoadConfig(const UIEditConfig &config);
public:
	virtual	void	RenderSelf(const UIRect *rect);

	virtual	void	OnMouseEntered(UINT flag,const UIPoint &point);
	virtual	void	OnMouseExited(UINT flag,const UIPoint &point);
	virtual	BOOL	OnMouseMove(UINT flag,const UIPoint &point);
	virtual	BOOL	OnLButtonDown(UINT flag,const UIPoint &point);
private:
	void	OnDetectedTextChanged();
private:
	UIEditConfig	config_;
	UIEditWindow	*window_holder_;
	friend class UIEditWindow;
};

class UIEditWindow : public NativeWindow
{
public:
	UIEditWindow();
	virtual const wchar_t *GetWindowClassName() const {return L"amao_edit_wnd";}
	virtual const wchar_t *GetSuperClassName() const  {return L"Edit"; }
	
	virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnDestroy();
	void	Init(UIEdit *edit);
private:
	UIEdit	*edit_owner_;
};