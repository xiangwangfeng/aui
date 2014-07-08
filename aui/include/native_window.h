/**
 * @file    native_window.h
 * @brief   基础的窗口类封装
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-9
 * @website www.xiangwangfeng.com
 */

#pragma once
#include <Windows.h>
#include <string>

class NativeWindow
{
public:
	NativeWindow();
	virtual ~NativeWindow();

	HWND GetHWND() const  {return hwnd_;}
	operator HWND() const {return hwnd_;}

	virtual const wchar_t *GetWindowClassName() const {return L"amao_native_window";}
	virtual const wchar_t *GetSuperClassName() const  {return NULL;}

	BOOL RegisterWindowClass();
	BOOL RegisterSuperClass();

	BOOL Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
    BOOL Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

	void ShowWindow(BOOL show = TRUE, BOOL take_focus = TRUE);
	void CenterWindow();
	void CloseWindow();

	void SetIcon(const wchar_t *icon_filepath);
	void SetIcon(int resource_id);
	void SetIcon(HICON icon);

	void SetWindowText(const wchar_t *text);
	void  GetWindowText(std::wstring &text);

	void SetTimer(UINT id, UINT elapse, TIMERPROC function = NULL);
	void KillTimer(UINT id);

	BOOL PostMessage(UINT message,WPARAM wParam = 0,LPARAM lParam = 0);
	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

	void	SetAsMainWindow() {is_main_window_ = TRUE;}
//消息循环
	virtual BOOL AfterCreated();
	virtual BOOL OnEraseBkgnd();
	virtual void OnTimer(UINT id);
	virtual void OnSize(UINT type,int cx,int cy);
	virtual void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual void OnDestroy();
public:
	static LRESULT CALLBACK StaticHandleMessages(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	HWND			hwnd_;
	BOOL			is_main_window_;
	WNDPROC			old_window_proc_;
};