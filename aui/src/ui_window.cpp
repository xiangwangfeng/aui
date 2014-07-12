/**
 * @file    ui_window.cpp
 * @brief   通用窗口类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#include "ui_window.h"
#include "ui_macros.h"
#include "ui_control.h"
#include "gdi_canvas.h"

UIWindow::UIWindow()
:is_closing_(FALSE),
resize_needed_(TRUE),
is_mouse_in_(FALSE),
current_mouse_control_(NULL),
root_control_(NULL)
{

}

UIWindow::~UIWindow()
{
	delete root_control_;
}

LRESULT	UIWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (is_closing_)
	{
		return __super::HandleMessages(message,wParam,lParam);
	}

	LRESULT message_handled_result = 0L;

	switch (message)
	{
	//绘制
	case WM_PAINT:
		HandleWMPaintMessage();
		message_handled_result = TRUE;
		break;
	//关闭
	case WM_CLOSE:
		is_closing_ = TRUE;
		break;
	//鼠标消息
	case WM_MOUSELEAVE:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_MOUSEWHEEL:
		{
			HandleMouseMessage(message,wParam,lParam);
		}
		break;
	default:
		break;
	}

	//如果设置为已处理就不需要调用基类方法
	return message_handled_result ? message_handled_result 
			: __super::HandleMessages(message, wParam, lParam);
}


void	UIWindow::AddRootControl(UIControl *root_control)
{
	delete root_control_;
	root_control_ = root_control;
	root_control_->SetParentWin(this);
}


void	UIWindow::UpdateLayout()
{
	resize_needed_ = TRUE;
	::InvalidateRect(hwnd_, NULL, FALSE);
}

void	UIWindow::Invalidate(const UIRect* rect)
{
	::InvalidateRect(hwnd_,rect,FALSE);
}

void	UIWindow::SetWindowMinSize(const UISize *size)
{
	PTR_VOID(size);
	min_size_ = *size;
}

void	UIWindow::SetWindowMinSize(int width,int height)
{
	SetWindowMinSize(&UISize(width,height));
}

void	UIWindow::SetWindowMaxSize(const UISize *size)
{
	PTR_VOID(size);
	max_size_ = *size;
}

void	UIWindow::SetWindowMaxSize(int width,int height)
{
	SetWindowMaxSize(&UISize(width,height));
}

void	UIWindow::AddNotifier(IUINotify *notifier)
{
	notifiers.push_back(notifier);
}

void	UIWindow::FireEvent(UINotifyEvent event,UIControl *contorl)
{
	for (size_t i = 0; i < notifiers.size(); i++)
	{
		notifiers[i]->Notify(event,contorl);
	}
}

void	UIWindow::OnSize(UINT type,int cx,int cy)
{
	__super::OnSize(type, cx, cy);
	DoUpdateLayout();
}

void	UIWindow::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	HMONITOR hmonitor = MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST);
	MONITORINFO minfo;
	minfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(hmonitor, &minfo);
	UIPoint offset(1,1);


	lpMMI->ptMaxPosition.x = minfo.rcWork.left - minfo.rcMonitor.left - offset.x;
	lpMMI->ptMaxPosition.y = minfo.rcWork.top - minfo.rcMonitor.top - offset.y;

	if (max_size_.cx != 0 && max_size_.cy != 0)
	{
		lpMMI->ptMaxSize.x = max_size_.cx + offset.x * 2;
		lpMMI->ptMaxSize.y = max_size_.cy + offset.y * 2;
		lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
		lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
	}

	if (min_size_.cx != 0 && min_size_.cy != 0)
	{
		lpMMI->ptMinTrackSize.x = min_size_.cx + offset.x * 2;
		lpMMI->ptMinTrackSize.y = min_size_.cy + offset.y * 2;
	}

	
}

//////////////////////////////////////私有方法////////////////////////////////////
void	UIWindow::Render(const UIRect *rect)
{
	if (root_control_)
	{
		root_control_->Render(rect);
	}
}

void	UIWindow::DoUpdateLayout()
{
	if (root_control_)
	{
		RECT rect;
		::GetClientRect(hwnd_,&rect);
		root_control_->SetRootFrame(&UIRect(rect));
	}
}

void	UIWindow::HandleWMPaintMessage()
{
	if (resize_needed_)
	{
		DoUpdateLayout();
		resize_needed_ = FALSE;
	}

	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(hwnd_, &ps);
	{
		RECT rect;
		GetClientRect(hwnd_,&rect);
		GDICanvas canvas(hdc,rect.right-rect.left,
			rect.bottom-rect.top);
		SetCurrentCanvas(&canvas);
		Render(&UIRect(rect));
		SetCurrentCanvas(NULL);

	}
	::EndPaint(hwnd_, &ps);
}

void	UIWindow::HandleMouseMessage(UINT message,WPARAM wParam,LPARAM lParam)
{
	if (message == WM_MOUSELEAVE)
	{
		SetCurrentMouseControl(NULL);
		is_mouse_in_ = FALSE;
		return;
	}

	if(message == WM_MOUSEMOVE)
	{
		if (!is_mouse_in_)
		{
			TRACKMOUSEEVENT track_mouse_event;
			track_mouse_event.cbSize = sizeof(TRACKMOUSEEVENT);
			track_mouse_event.dwFlags = TME_LEAVE;
			track_mouse_event.hwndTrack = GetHWND();
			is_mouse_in_ =  TrackMouseEvent(&track_mouse_event);
		}
	}

	if (message == WM_LBUTTONDOWN)
	{
		::SetFocus(hwnd_);
	}


	if (root_control_)
	{
		UIPoint	point((short)LOWORD(lParam), (short)HIWORD(lParam));
		UIControl *mouse_control = root_control_->LookupMouseFocusedControl(point);
		if (message == WM_MOUSEMOVE)
		{
			SetCurrentMouseControl(mouse_control);
		}
		mouse_control->DispatchMouseMessage(message,wParam,lParam);
	}
}

void	UIWindow::SetCurrentMouseControl(UIControl *control)
{
	if (current_mouse_control_ == control)
	{
		return;
	}
	if (current_mouse_control_)
	{
		current_mouse_control_->DispatchMouseMessage(WM_MOUSELEAVE,0,0);
	}
	if (control)
	{
		control->DispatchMouseMessage(WM_MOUSEHOVER,0,0);
	}
	current_mouse_control_ = control;
}