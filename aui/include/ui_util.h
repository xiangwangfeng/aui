/**
 * @file    ui_util.h
 * @brief   UI辅助方法
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-7-7
 * @website www.xiangwangfeng.com
 */
#pragma once
#include <string>
#include "ui_base.h"

namespace AUI{

std::wstring UTF8toUTF16(const char *source);
void GetDefaultUIFont(UIFont &font);
UIFont *GetGlobalEditFont();
void SafeOpenURL(const wchar_t *url,int flag = SW_SHOWMAXIMIZED, BOOL use_default_browser = TRUE);

};