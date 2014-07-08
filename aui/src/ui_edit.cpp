/**
 * @file    ui_edit.cpp
 * @brief   UIEdit
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-11
 * @website www.xiangwangfeng.com
 */
#include "ui_edit.h"
#include <WindowsX.h>
#include <OleCtl.h>
#include "ui_base.h"
#include "ui_util.h"
#include "ui_canvas.h"
#include "ui_window.h"

UIEditConfig::UIEditConfig()
:border_color_(RGB(0,0,0)),
text_color_(RGB(0,0,0)),
is_password_edit_(FALSE)
{

}

UIEdit::UIEdit()
{

}

const wchar_t *UIEdit::GetEditText() const
{
	return config_.text_.c_str();
}

void	UIEdit::SetEditText(const wchar_t *text,BOOL redraw)
{
	config_.text_ = text;
	if (redraw)
	{
		SetNeedDisplay();
	}
}

void	UIEdit::SetBorderColor(UIColor color)
{
	config_.border_color_ = color;
}

void	UIEdit::SetTextColor(UIColor color)
{
	config_.text_color_ = color;
}

void	UIEdit::SetAsPasswordEdit(BOOL is_password_edit)
{
	config_.is_password_edit_ = is_password_edit;
}


void	UIEdit::LoadConfig(const UIEditConfig &config)
{
	config_ = config;
	SetNeedDisplay();
}

void	UIEdit::RenderSelf(const UIRect *rect)
{
	UICanvas *canvas = CurrentCanvas();
	canvas->Rectangle(&frame_,config_.border_color_);

	UIRect text_rect = frame_;
	text_rect.Inflate(-3,0);

	const wchar_t *text = NULL;
	std::wstring unicode_text;
	if (config_.is_password_edit_)
	{
		for (size_t i = 0; i < config_.text_.length(); i++)
		{
			unicode_text += L"*";
		}
		text = unicode_text.c_str();
	}
	else
	{
		text = config_.text_.c_str();
	}

	canvas->DrawText(text,config_.text_.length(),&text_rect,config_.text_color_,
					kTextAlignmentVCenter | DT_SINGLELINE| DT_NOPREFIX | DT_EDITCONTROL,
					AUI::GetGlobalEditFont());
}

void	UIEdit::OnMouseEntered(UINT flag,const UIPoint &point)
{
	SetCursor(IDC_IBEAM);
}

void	UIEdit::OnMouseExited(UINT flag,const UIPoint &point)
{
	SetCursor(IDC_ARROW);
}

BOOL	UIEdit::OnMouseMove(UINT flag,const UIPoint &point)
{
	SetCursor(IDC_IBEAM);
	return TRUE;
}

BOOL	UIEdit::OnLButtonDown(UINT flag,const UIPoint &point)
{
	UIEditWindow *window = new UIEditWindow();
	window->Init(this);
	window_holder_ = window;
	return TRUE;
}

void	UIEdit::OnDetectedTextChanged()
{
	SendNotify(kEventTextChanged);
}


UIEditWindow::UIEditWindow()
:edit_owner_(NULL)
{

}


void	UIEditWindow::Init(UIEdit *edit)
{
	UIRect rect = edit->GetFrame();
	rect.Deflate(1, 3);
	DWORD style = WS_CHILD | ES_AUTOHSCROLL;
	if (edit->config_.is_password_edit_)
	{
		style |= ES_PASSWORD;
	}
	Create(edit->GetParentWin()->GetHWND(), NULL, style, 0, rect);
	HWND hwnd = GetHWND();
	HFONT font = CreateFontIndirect(AUI::GetGlobalEditFont());
	SetWindowFont(hwnd,font, TRUE);
	SetWindowText(edit->config_.text_.c_str());
	Edit_SetModify(hwnd, TRUE);
	SendMessage(EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(2, 2));
	Edit_SetSel(hwnd, 0, -1);
	::ShowWindow(hwnd, SW_SHOWNOACTIVATE);
	::SetFocus(hwnd);
	edit_owner_ =  edit;
}

LRESULT	UIEditWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KILLFOCUS )
	{
		std::wstring text;
		GetWindowText(text);
		edit_owner_->SetEditText(text.c_str(),TRUE);
		PostMessage(WM_CLOSE);
	}
	else if (message == WM_KEYUP)
	{
		std::wstring text;
		GetWindowText(text);
		if (wcscmp(edit_owner_->GetEditText(),text.c_str()) != 0)
		{
			edit_owner_->SetEditText(text.c_str());
			edit_owner_->OnDetectedTextChanged();
		}

	}
	return __super::HandleMessages(message, wParam, lParam);
}

void	UIEditWindow::OnDestroy()
{
	__super::OnDestroy();
	edit_owner_->window_holder_ = NULL;
	delete this;
}
