/**
 * @file    ui_button.cpp
 * @brief   UIButton
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-3
 * @website www.xiangwangfeng.com
 */
#include "ui_button.h"
#include "ui_util.h"
#include "ui_canvas.h"

UIButtonConfig::UIButtonConfig()
:text_normal_color_(RGB(0,0,0)),
text_focus_color_(RGB(0,0,0)),
text_disable_color_(RGB(163,163,163)),
text_alignment_(kTextAlignmentCenter)
{
	AUI::GetDefaultUIFont(font_);
}


UIButton::UIButton()
:button_status_(kUIButtonStatusNormal),
self_clicked_(FALSE)
{

}

void	UIButton::SetText(const wchar_t *text)
{
	config_.button_text_ = text;
	SetNeedDisplay();
}

void	UIButton::SetNormalImage(const wchar_t *filepath)
{
	config_.normal_image_ = filepath;
}

void	UIButton::SetHoverImage(const wchar_t *filepath)
{
	config_.hover_image_ = filepath;
}

void	UIButton::SetPressedImage(const wchar_t *filepath)
{
	config_.pressed_image_ = filepath;
}

void	UIButton::SetDisabledImage(const wchar_t *filepath)
{
	config_.disabled_image_ = filepath;
}

void	UIButton::SetTextColor(UIColor color)
{
	config_.text_normal_color_ = color;
}

void	UIButton::SetFocusTextColor(UIColor color)
{
	config_.text_focus_color_ = color;
}

void	UIButton::SetDisableTextColor(UIColor color)
{
	config_.text_normal_color_ = color;
}

void	UIButton::SetTextOffset(const UIPoint &offset)
{
	config_.text_offset_ = offset;
}

void	UIButton::SetTextAlignment(TextAlignment alignment)
{
	config_.text_alignment_ = alignment;
}

void	UIButton::SetTextFont(const UIFont &font)
{
	config_.font_ = font;
}

void	UIButton::LoadButtonConfig(const UIButtonConfig &config)
{
	config_ = config;
	SetNeedDisplay();
}


void	UIButton::OnMouseEntered(UINT flag,const UIPoint &point)
{
	SetButtonStatus(kUIButtonStatusHover);
}

void	UIButton::OnMouseExited(UINT flag,const UIPoint &point)
{
	SetButtonStatus(kUIButtonStatusNormal);
	self_clicked_ = FALSE;
}

BOOL	UIButton::OnLButtonDown(UINT flag,const UIPoint &point)
{
	SetButtonStatus(kUIButtonStatusPressed);
	self_clicked_ = TRUE;
	return TRUE;
}

BOOL	UIButton::OnLButtonUp(UINT flag,const UIPoint &point)
{
	SetButtonStatus(kUIButtonStatusHover);
	if (self_clicked_)
	{
		OnClicked();
		self_clicked_ = FALSE;
	}
	return TRUE;
}

void	UIButton::RenderSelf(const UIRect *rect)
{
	UICanvas *canvas = CurrentCanvas();
	BOOL enabled = IsEnabled();
	if (!enabled)
	{
		button_status_ = kUIButtonStatusDisable;
	}
	switch(button_status_)
	{
		case kUIButtonStatusNormal:
			if (!config_.normal_image_.empty())
			{
				canvas->DrawImage(config_.normal_image_,&frame_);
			}
			break;
		case kUIButtonStatusHover:
			if (!config_.hover_image_.empty())
			{
				canvas->DrawImage(config_.hover_image_,&frame_);
			}
			break;
		case kUIButtonStatusPressed:
			if (!config_.pressed_image_.empty())
			{
				canvas->DrawImage(config_.pressed_image_,&frame_);
			}
			break;
		case kUIButtonStatusDisable:
			if (!config_.disabled_image_.empty())
			{
				canvas->DrawImage(config_.disabled_image_,&frame_);
			}
			break;
		default:
			break;
	}
	DrawText();
}


//////////////////////////////////Ë½ÓÐ·½·¨////////////////////////////////////////
void	UIButton::SetButtonStatus(UIButtonStatus status)
{
	button_status_ = status;
	SetNeedDisplay();
}

void	UIButton::DrawText()
{
	if (!config_.button_text_.empty())
	{
		UIColor color = config_.text_normal_color_;
		if (button_status_ == kUIButtonStatusHover || 
			button_status_ == kUIButtonStatusPressed)
		{
			color = config_.text_focus_color_;
		}
		else if(button_status_ == kUIButtonStatusDisable)
		{
			color = config_.text_disable_color_;
		}
		UIPoint &offset = config_.text_offset_;
		int width = frame_.GetWidth();
		int height= frame_.GetHeight();
		int x = frame_.GetX() + offset.x;
		int y = frame_.GetY() + offset.y;
		UIRect text_rect(x,y,width,height);

		std::wstring &button_text = config_.button_text_;
		UICanvas *canvas = CurrentCanvas();
		canvas->DrawText(button_text.c_str(),button_text.length(),&text_rect,color,
			config_.text_alignment_ | DT_VCENTER | DT_SINGLELINE,&config_.font_);
		
	}
}

void	UIButton::OnClicked()
{
	SendNotify(kEventClick);
}