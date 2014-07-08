/**
 * @file    ui_label.cpp
 * @brief   UILabel
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-9
 * @website www.xiangwangfeng.com
 */

#include "ui_label.h"
#include "ui_canvas.h"
 #include "ui_util.h"

UILableConfig::UILableConfig()
:text_color_(RGB(0,0,0)),
text_link_color_(RGB(0,91,202)),
is_hyperlink_(FALSE),
is_single_line_(TRUE),
always_show_underline_(FALSE),
hor_alignment_(kTextAlignmentVCenter),
ver_alignment_(kTextAlignmentCenter)
{
	AUI::GetDefaultUIFont(font_);
}

UILabel::UILabel()
:is_mouse_in_(FALSE),
self_clicked_(FALSE)
{

}

void	UILabel::SetText(const wchar_t *text)
{
	config_.text_ = text;
	SetNeedDisplay();
}

void	UILabel::SetBkImage(const wchar_t *filepath)
{
	config_.bk_image_ = filepath;
}

void	UILabel::SetTextColor(UIColor color)
{
	config_.text_color_ = color;
}

void	UILabel::SetTextLinkColor(UIColor color)
{
	config_.text_link_color_ = color;
}

void	UILabel::SetURL(const wchar_t *url)
{
	config_.url_ = url;
	config_.is_hyperlink_ = TRUE;
}

void	UILabel::SetAsHyperLink(BOOL is_hyperlink)
{
	config_.is_hyperlink_ = is_hyperlink;
}

void	UILabel::SetSingleLine(BOOL is_single_line)
{
	config_.is_single_line_ = is_single_line;
}

void	UILabel::SetShowUnderLine(BOOL show_underline)
{
	config_.always_show_underline_ = show_underline;
}

void	UILabel::SetTextAlignment(TextAlignment hor_alignment,TextAlignment ver_alignment)
{
	config_.hor_alignment_ = hor_alignment;
	config_.ver_alignment_ = ver_alignment;
}

void	UILabel::SetTextFont(const UIFont &font)
{
	config_.font_ = font;
}




void	UILabel::LoadConfig(const UILableConfig &config)
{
	config_ = config;
	SetNeedDisplay();
}

void	UILabel::RenderSelf(const UIRect *rect)
{
	UICanvas *canvas = CurrentCanvas();
	//绘制背景
	if (!config_.bk_image_.empty())
	{
		canvas->DrawImage(config_.bk_image_,&frame_);
	}

	//颜色
	UIColor color = config_.is_hyperlink_ ? config_.text_link_color_ : config_.text_color_;
	//format
	UINT format = config_.hor_alignment_ | config_.ver_alignment_;
	if (config_.is_single_line_)
	{
		format |= DT_SINGLELINE;
	}
	else
	{
		format |= DT_WORDBREAK;
	}
	//下划线
	config_.font_.lfUnderline = (config_.always_show_underline_ ||
								(config_.is_hyperlink_ && is_mouse_in_));

	canvas->DrawText(config_.text_.c_str(),config_.text_.length(),
		&frame_,color,format,&config_.font_);
}

void	UILabel::OnMouseEntered(UINT flag,const UIPoint &point)
{
	is_mouse_in_  = TRUE;
	if (config_.is_hyperlink_)
	{
		SetCursor(IDC_HAND);
		if(!config_.always_show_underline_)
		{
			SetNeedDisplay();
		}
	}
}

void	UILabel::OnMouseExited(UINT flag,const UIPoint &point)
{
	is_mouse_in_	= FALSE;
	self_clicked_	= FALSE;
	SetCursor(IDC_ARROW);
	if(!config_.always_show_underline_ && config_.is_hyperlink_)
	{
		SetNeedDisplay();
	}
}

BOOL	UILabel::OnMouseMove(UINT flag,const UIPoint &point)
{
	is_mouse_in_  = TRUE;
	if (config_.is_hyperlink_)
	{
		SetCursor(IDC_HAND);
	}
	return TRUE;
}

BOOL	UILabel::OnLButtonDown(UINT flag,const UIPoint &point)
{
	self_clicked_ = TRUE;
	return TRUE;
}

BOOL	UILabel::OnLButtonUp(UINT flag,const UIPoint &point)
{
	if (self_clicked_ && config_.is_hyperlink_)
	{
		OnClicked();
		self_clicked_ = FALSE;
	}
	return TRUE;
}



void	UILabel::OnClicked()
{
	SetCursor(IDC_HAND);
	if (config_.is_hyperlink_)
	{
		AUI::SafeOpenURL(config_.url_.c_str());
	}
}