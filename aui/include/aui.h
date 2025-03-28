/**
 * @file    aui.h
 * @brief   ui库头文件
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-9
 * @website www.xiangwangfeng.com
 */

#pragma 
#include "ui_macros.h"
#include "ui_util.h"
#include "ui_base.h"
#include "ui_window.h"
#include "ui_control.h"
#include "ui_panel.h"
#include "ui_label.h"
#include "ui_button.h"
#include "ui_edit.h"
#include "ui_image.h"


enum class RenderBackend { GDIPlus, D2D };

void	InitAUI();
void	CleanUpAUI();
void	SetRenderBackend(RenderBackend backend);
RenderBackend	GetCurrentRenderBackend();