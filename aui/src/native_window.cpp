/**
 * @file    native_window.cpp
 * @brief   基础的窗口类封装
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-9
 * @website www.xiangwangfeng.com
 */

#include "native_window.h"
#include <Windows.h>
#include <WindowsX.h>
#include "ui_macros.h"

NativeWindow::NativeWindow()
:hwnd_(NULL),
is_main_window_(FALSE),
old_window_proc_(::DefWindowProc)
{
	
}

NativeWindow::~NativeWindow()
{

}

BOOL	NativeWindow::RegisterWindowClass()
{
	WNDCLASSEX wcx = {0}; 
	wcx.cbSize = sizeof(WNDCLASSEX);							// size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;						// redraw if size changes 
	wcx.lpfnWndProc = NativeWindow::StaticHandleMessages;		// points to window procedure 
	wcx.cbClsExtra = 0;											// no extra class memory 
	wcx.cbWndExtra = 0;											// no extra window memory 
	wcx.hInstance = NULL;										// handle to instance 
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// predefined app. icon 
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);					// predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// white background brush 
	wcx.lpszMenuName = NULL;									// name of menu resource 
	wcx.lpszClassName = GetWindowClassName();						// name of window class 
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);				// small class icon 

	return RegisterClassEx(&wcx) != 0 || 
		::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

BOOL	NativeWindow::RegisterSuperClass()
{
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	if(!::GetClassInfoEx(NULL, GetSuperClassName(), &wc))
	{
		if( !::GetClassInfoEx(NULL, GetSuperClassName(), &wc) ) 
		{
			return FALSE;
		}
	}
	old_window_proc_ = wc.lpfnWndProc;
	wc.lpfnWndProc = NativeWindow::StaticHandleMessages;
	wc.hInstance = NULL;
	wc.lpszClassName = GetWindowClassName();
	ATOM result = ::RegisterClassEx(&wc);
	return result != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

BOOL	NativeWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x /* = CW_USEDEFAULT */, int y /* = CW_USEDEFAULT */, int cx /* = CW_USEDEFAULT */, int cy /* = CW_USEDEFAULT */, HMENU hMenu /* = NULL */)
{
	BOOL created = FALSE;
	if (GetSuperClassName() != NULL)
	{
		if (!RegisterSuperClass())
		{
			return FALSE;
		}
	}
	else
	{
		if(!RegisterWindowClass())
		{
			return FALSE;
		}
	}

	hwnd_ = ::CreateWindowEx(dwExStyle, GetWindowClassName(), pstrName, dwStyle, x, y, cx, cy, hwndParent, hMenu, NULL, this);
	if (hwnd_ != NULL)
	{
		created = AfterCreated();
	}
	return created;
}

BOOL	NativeWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu /* = NULL */)
{
	return Create(hwndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu);
}

void	NativeWindow::ShowWindow(BOOL show /* = TRUE */, BOOL take_focus /* = TRUE */)
{
	assert(::IsWindow(hwnd_));
	if( !::IsWindow(hwnd_) ) 
		return;
	::ShowWindow(hwnd_, show ? (take_focus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

void	NativeWindow::CenterWindow()
{
	assert(::IsWindow(hwnd_));
	assert((GetWindowStyle(hwnd_) & WS_CHILD)==0);
	RECT window_rect = { 0 };
	::GetWindowRect(hwnd_, &window_rect);
	RECT area_rect = { 0 };
	RECT center_rect = { 0 };
	HWND hWndParent = ::GetParent(hwnd_);
	HWND hWndCenter = ::GetWindowOwner(hwnd_);
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &area_rect, NULL);
	if( hWndCenter == NULL ) 
		center_rect = area_rect; 
	else 
		::GetWindowRect(hWndCenter, &center_rect);

	int width = window_rect.right - window_rect.left;
	int height = window_rect.bottom - window_rect.top;

	int left_x = (center_rect.left + center_rect.right) / 2 - width / 2;
	int top_y = (center_rect.top + center_rect.bottom) / 2 - height / 2;

	if( left_x < area_rect.left ) 
		left_x = area_rect.left;
	else if( left_x + width > area_rect.right ) 
		left_x = area_rect.right - width;
	if( top_y < area_rect.top ) 
		top_y = area_rect.top;
	else if( top_y + height > area_rect.bottom ) 
		top_y = area_rect.bottom - height;
	::SetWindowPos(hwnd_, NULL, left_x, top_y, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void	NativeWindow::CloseWindow()
{
	assert(::IsWindow(hwnd_));
	::PostMessage(hwnd_,WM_CLOSE,0,0);
}

void	NativeWindow::SetIcon(const wchar_t *icon_filepath)
{
	assert(::IsWindow(hwnd_));
	PTR_VOID(icon_filepath);
	HICON icon = (HICON)LoadImage(NULL,icon_filepath,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	SetIcon(icon);
}

void	NativeWindow::SetIcon(int resource_id)
{
	assert(::IsWindow(hwnd_));
	LPCWSTR A =  MAKEINTRESOURCE(resource_id);
	HICON icon = (HICON)::LoadImage(NULL, MAKEINTRESOURCE(resource_id), IMAGE_ICON, 
		::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(icon);
}

void	NativeWindow::SetIcon(HICON icon)
{
	assert(::IsWindow(hwnd_));
	PTR_VOID(icon);
	::SendMessage(hwnd_, WM_SETICON, (WPARAM)TRUE, (LPARAM)icon);
	::SendMessage(hwnd_, WM_SETICON, (WPARAM)FALSE, (LPARAM)icon);
}
void	NativeWindow::SetWindowText(const wchar_t *text)
{
	assert(::IsWindow(hwnd_));
	PTR_VOID(text);
	::SetWindowText(hwnd_,text);
}

void		NativeWindow::GetWindowText(std::wstring &text)
{
	assert(::IsWindow(hwnd_));
	text.empty();
	int length = ::GetWindowTextLength(hwnd_) + 1;
	wchar_t *temp_text = static_cast<wchar_t *>(_alloca(length * sizeof(wchar_t)));
	::GetWindowText(hwnd_,temp_text, length);
	text = temp_text;
}


void	NativeWindow::SetTimer(UINT id, UINT elapse, TIMERPROC function)
{
	assert(::IsWindow(hwnd_));
	::SetTimer(hwnd_,id,elapse,function);
}

void	NativeWindow::KillTimer(UINT id)
{
	assert(::IsWindow(hwnd_));
	::KillTimer(hwnd_,id);
}

BOOL	NativeWindow::PostMessage(UINT message,WPARAM wParam /* = 0 */,LPARAM lParam /* = 0 */)
{
	assert(::IsWindow(hwnd_));
	return ::PostMessage(hwnd_,message,wParam,lParam);
}

LRESULT	NativeWindow::SendMessage(UINT message, WPARAM wParam /* = 0 */, LPARAM lParam /* = 0 */)
{
	assert(::IsWindow(hwnd_));
	return ::SendMessage(hwnd_,message,wParam,lParam);
}

LRESULT	NativeWindow::StaticHandleMessages(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT *lpcs = (CREATESTRUCT*)lParam;
		NativeWindow *native_window = (NativeWindow *)lpcs->lpCreateParams;
		native_window->hwnd_ = hwnd;
		SetWindowLong(hwnd, GWL_USERDATA, (LPARAM)native_window);
	}
	else if (message == WM_NCDESTROY)
	{
		NativeWindow *native_window = (NativeWindow *)GetWindowLong(hwnd, GWL_USERDATA);
		if (native_window)
		{
			LRESULT result = ::CallWindowProc(native_window->old_window_proc_, hwnd, message, wParam, lParam);
			::SetWindowLongPtr(native_window->GetHWND(), GWLP_USERDATA, 0L);
			native_window->OnDestroy();
			return result;
		}
	}

	NativeWindow *native_window = (NativeWindow *)GetWindowLong(hwnd, GWL_USERDATA);
	if (native_window)
		return native_window->HandleMessages(message, wParam, lParam);
	else
		return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT NativeWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_ERASEBKGND:
			return OnEraseBkgnd();
		case WM_TIMER:
			{
				OnTimer((UINT)wParam);
			}
			break;
		case WM_SIZE:
			{
				int cx = LOWORD(lParam);
				int cy = HIWORD(lParam);
				OnSize((UINT)wParam,cx,cy);
			}
			break;
		case WM_GETMINMAXINFO:
			{
				OnGetMinMaxInfo((MINMAXINFO *)lParam);
			}
			break;
		default:
			break;;
	}
	return CallWindowProc(old_window_proc_,hwnd_, message, wParam, lParam);
}

BOOL	NativeWindow::AfterCreated()
{
	return TRUE;
}

BOOL	NativeWindow::OnEraseBkgnd()
{
	return TRUE;
}

void	NativeWindow::OnTimer(UINT id)
{

}

void	NativeWindow::OnSize(UINT type,int cx,int cy)
{
	if (::GetFocus() != hwnd_)
	{
		::SetFocus(hwnd_);
	}
}

void	NativeWindow::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	
}

void	NativeWindow::OnDestroy()
{
	if (is_main_window_)
	{
		::PostQuitMessage(0);
	}
}