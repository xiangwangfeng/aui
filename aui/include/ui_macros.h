/**
 * @file    ui_macros.h
 * @brief   ui宏定义
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-6-24
 * @website www.xiangwangfeng.com
 */
#pragma once
#include <cassert>

#define PTR_VOID(p)				{ assert(p); if (NULL == p) { return; } }