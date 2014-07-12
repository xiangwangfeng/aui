/**
 * @file    ui_panel.cpp
 * @brief   UIPanel
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-6-20
 * @website www.xiangwangfeng.com
 */
#include "ui_panel.h"
#include "ui_util.h"
#include "ui_canvas.h"
void	UIPanel::SetBKColor(UIColor color)
{
	bk_color_ = color;
}

void	UIPanel::SetBKImage(const std::wstring &filepath)
{
	bk_filepath_ = filepath;
}

void	UIPanel::RenderSelf(const UIRect *rect)
{
	UICanvas *canvas = CurrentCanvas();
	canvas->FillRect(&frame_,bk_color_);

	if (!bk_filepath_.empty())
	{
		canvas->DrawImage(bk_filepath_,&frame_);
	}
}
