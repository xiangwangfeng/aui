/**
 * @file    ui_macros.h
 * @brief   ui∫Í∂®“Â
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-6-24
 * @website www.xiangwangfeng.com
 */
#pragma once
#include <cassert>

#define PTR_VOID(p)				{ assert(p); if (NULL == p) { return; } }