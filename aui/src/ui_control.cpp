/**
 * @file    ui_control.cpp
 * @brief   UI控件基类
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @data	2012-4-22
 * @website www.xiangwangfeng.com
 */

#include "ui_control.h"
#include "ui_macros.h"
#include "ui_window.h"
#include "ui_canvas.h"

UIControl::UIControl()
:parent_(NULL),
parent_win_(NULL),
tag_(0),
visible_(TRUE),
parent_visible_(TRUE),
enabled_(TRUE),
parent_enabled_(TRUE),
alignment_type_(kAlignmentLeftTop)
{
}

UIControl::~UIControl()
{
	for (size_t i = 0; i < children_.size(); i++)
	{
		delete children_[i];
	}
}

void	UIControl::SetAttribute(const char *name,const char *value)
{
	if (strcmp(name,"name") == 0)
	{
		SetControlName(value);
	}
	else if (strcmp(name,"tag") == 0)
	{
		SetTag(atoi(value));
	}
	else if (strcmp(name,"alignment") == 0)
	{
		Alignment alignment = GetAlignmentByString(value);
		SetAlignmentType(alignment);
	}
	else if (strcmp(name,"size") == 0)
	{
		UISize size;
		sscanf(value,"%d,%d",&size.cx,&size.cy);
		SetSize(size);
	}
	else if (strcmp(name,"margin") == 0)
	{
		UIMargin margin;
		sscanf(value,"%d,%d,%d,%d",
			&margin.left,&margin.top,&margin.right,&margin.bottom);
		SetMargin(margin);
	}
	else if (strcmp(name,"visible") == 0)
	{
		SetVisible(stricmp(value,"true") == 0);
	}
	else if (strcmp(name,"enable") == 0)
	{
		SetEnabled(stricmp(value,"true") == 0);
	}

}

void	UIControl::SetControlName(const char *name)
{
	name_ = name;
}

std::string	UIControl::GetControlName() const
{
	return name_;
}

void	UIControl::SetTag(int tag)
{
	tag_ = tag;
}

int		UIControl::GetTag() const
{
	return tag_;
}

void	UIControl::SetMargin(const UIMargin &margin)
{
	margin_ = margin;
	SetNeedLayout();
}

void	UIControl::SetMargin(int left,int top /* = 0 */,int right /* = 0 */,int bottom /* = 0 */)
{
	SetMargin(UIMargin(left,top,right,bottom));
}

void	UIControl::SetSize(const UISize &size)
{
	size_ = size;
	SetNeedLayout();
}

void	UIControl::SetSize(int width,int height)
{
	SetSize(UISize(width,height));
}

UISize	UIControl::GetSize() const
{
	return size_;
}

void	UIControl::SetAlignmentType(Alignment type)
{
	alignment_type_ = type;
	SetNeedLayout();
}

Alignment	UIControl::GetAlignmentType() const
{
	return alignment_type_;
}

void	UIControl::SetVisible(BOOL visible)
{
	visible_ = visible;
	
	//递归设置子控件父亲可见性
	for (size_t i = 0; i < children_.size(); i++)
	{
		children_[i]->SetParentVisibleRecursive(visible);
	}
}

BOOL	UIControl::IsVisible() const
{
	return parent_visible_ && visible_;
}

void	UIControl::SetEnabled(BOOL enabled)
{
	enabled_ = enabled;

	//递归设置子控件父亲可用性
	for (size_t i = 0; i < children_.size(); i++)
	{
		children_[i]->SetParentEnabledRecursive(enabled);
	}
}

BOOL	UIControl::IsEnabled() const
{
	return parent_enabled_ && enabled_;
}


void	UIControl::SetParent(UIControl *control)
{
	PTR_VOID(control);
	parent_	=	control;
}

UIControl*	UIControl::GetParent() const
{ 
	return parent_;
}

UIWindow*	UIControl::GetParentWin() 
{
	if (parent_win_ == NULL && parent_)
	{
		parent_win_ = parent_->GetParentWin();
	}
	return parent_win_;
}

void	UIControl::AddSubControl(UIControl *control)
{
	PTR_VOID(control);
	control->SetParent(this);
	children_.push_back(control);
}

void	UIControl::RemoveSubControl(const std::string &name)
{
	if (name.empty())
	{
		return;
	}
	for (std::vector<UIControl *>::iterator it = children_.begin();
		it != children_.end(); it++)
	{
		if (name.compare((*it)->GetControlName()) == 0)
		{
			children_.erase(it);
			delete *it;
			break;
		}
	}
}

void	UIControl::Render(const UIRect *parent_rect)
{
	//生成裁剪区域
	UIRect rect = UIRect::IntersectRect(&frame_,parent_rect);
	CurrentCanvas()->SelectClipedRect(&rect);
	RenderSelf(&rect);

	//绘制子控件
	for (size_t i = 0; i <children_.size(); i++)
	{
		UIControl *child = children_[i];
		if (child->IsVisible())
		{
			child->Render(&rect);
		}
	}
}

void	UIControl::RenderSelf(const UIRect *rect)
{
	//由子控件绘制
}

void	UIControl::ArrangeSelf(const UIRect *parent_frame)
{
	int x = 0;
	int y = 0;
	int width  = size_.cx;
	int height = size_.cy;
	switch(alignment_type_)
	{
		//绝对定位
	case kAlignmentLeftTop:
		{
			x = parent_frame->GetX() + margin_.left;;
			y = parent_frame->GetY() + margin_.top;
			break;
		}
	case kAlignmentLeftCenter:
		{
			x = parent_frame->GetX() + margin_.left;
			y = parent_frame->GetY() + ((parent_frame->GetHeight() - size_.cy) >> 1);
			break;
		}
	case  kAlignmentLeftBottom:
		{
			x = parent_frame->GetX() + margin_.left;
			y = parent_frame->GetY() + parent_frame->GetHeight() - size_.cy - margin_.bottom;
			break;
		}
	case kAlignmentCenterTop:
		{
			x = parent_frame->GetX() + ((parent_frame->GetWidth() - size_.cx) >> 1) ;
			y = parent_frame->GetY() + margin_.top;
			break;
		}
	case  kAlignmentCenter:
		{
			x = parent_frame->GetX() + ((parent_frame->GetWidth() - size_.cx) >> 1);
			y = parent_frame->GetY() + ((parent_frame->GetHeight() - size_.cy) >> 1);
			break;
		}
	case  kAlignmentCenterBottom:
		{
			x = parent_frame->GetX() + ((parent_frame->GetWidth() - size_.cx) >> 1);
			y = parent_frame->GetY() + parent_frame->GetHeight() - size_.cy - margin_.bottom;
			break;
		}
	case kAlignmentRightTop:
		{
			x = parent_frame->GetX() +  parent_frame->GetWidth() - size_.cx - margin_.right;
			y = parent_frame->GetY() + margin_.top;
			break;
		}
	case kAlignmentRightCenter:
		{
			x = parent_frame->GetX() +  parent_frame->GetWidth() - size_.cx - margin_.right;
			y = parent_frame->GetY() + ((parent_frame->GetHeight() - size_.cy) >> 1);
			break;
		}
	case kAlignmentRightBottom:
		{
			x = parent_frame->GetX() +  parent_frame->GetWidth() - size_.cx - margin_.right;
			y = parent_frame->GetY() + parent_frame->GetHeight() - size_.cy - margin_.bottom;
			break;
		}
		//相对定位
	case kAlignmentLeft:
		{
			x		= parent_frame->GetX() + margin_.left;
			y		= parent_frame->GetY() + margin_.top;
			height	= parent_frame->GetHeight() - margin_.top - margin_.bottom;
			break;
		}
	case  kAlignmentRight:
		{
			x		= parent_frame->GetX() + parent_frame->GetWidth() - size_.cx - margin_.right;
			y		= parent_frame->GetY() + margin_.top;
			height	= parent_frame->GetHeight() - margin_.top - margin_.bottom;
			break;
		}
	case kAlignmentTop:
		{
			x		= parent_frame->GetX() + margin_.left;
			y		= parent_frame->GetY() + margin_.top;
			width	= parent_frame->GetWidth() - margin_.left - margin_.right;
			break;
		}
	case kAlignmentBottom:
		{
			x		= parent_frame->GetX() + margin_.left;
			y		= parent_frame->GetY() + parent_frame->GetHeight() - size_.cy - margin_.bottom;
			width	= parent_frame->GetWidth() - margin_.left - margin_.right;
			break;
		}
	case kAlignmentFill:
		{

			x		= parent_frame->GetX() + margin_.left;
			y		= parent_frame->GetY() + margin_.top;
			width	= parent_frame->GetWidth() - margin_.left - margin_.right ;
			height	= parent_frame->GetHeight() - margin_.top - margin_.bottom;
			break;
		}
	default:
		assert(0);
		break;
	}

	frame_ = UIRect(x,y,width,height);
}

UIControl*	UIControl::LookupMouseFocusedControl(const UIPoint &point)
{
	UIControl *find_control = this;

	for (size_t i = children_.size(); i > 0; i--)
	{
		UIControl *control = children_[i - 1];
		if (control->IsVisible() && control->IsEnabled()
			&& control->IsMouseInControl(point))
		{
			find_control = control->LookupMouseFocusedControl(point);
			break;
		}
	}

	return find_control;
}


void	UIControl::SetRootFrame(const UIRect *rect)
{
	SetFrame(rect);
	ArrangeChildren(&frame_);
}

void	UIControl::SetFrame(const UIRect *rect)
{
	PTR_VOID(rect);
	frame_ = *rect;
}

UIRect	UIControl::GetFrame() const
{
	return frame_;
}

void	UIControl::SetNeedLayout()
{
	UIWindow *parent_win = GetParentWin();
	if (parent_win)
	{
		parent_win->UpdateLayout();
	}
}

void	UIControl::SetNeedDisplay()
{
	UIWindow *parent_win = GetParentWin();
	if (parent_win)
	{
		parent_win->Invalidate(NULL);
	}
}

void	UIControl::SetCursor(const wchar_t *cursor_name)
{
	::ShowCursor(FALSE);
	::SetCursor(LoadCursor(NULL,cursor_name));	
	::ShowCursor(TRUE);
}

BOOL	UIControl::OnMouseMessage(UINT message,WPARAM wParam,LPARAM lParam)
{
	UIPoint	point((short)LOWORD(lParam), (short)HIWORD(lParam));
	UINT flag = (UINT)wParam;
	//message_handled说明：如果返回TRUE则消息不继续往父控件抛

	//对于WM_MOUSEHOVE的message_handled的处理可以有三种作法
	//1.OnMouseEntered添加返回值，有重写方法来判断
	//2.默认设置为TRUE，认为鼠标从父控件进入子控件后，控件即变为非HOVER状态
	//3.默认设置为FALSE，认为鼠标只要控件中，不管有没有进入到子控件中，它都为HOVER状态
	//本库采用第二种作法
	BOOL message_handled = FALSE;
	switch(message)
	{
	case WM_MOUSEHOVER:
		OnMouseEntered(flag,point);
		message_handled = TRUE;	
		break;
	case WM_MOUSELEAVE:
		OnMouseExited(flag,point);
		message_handled = TRUE;	//WM_MOUSELEAVE  无需往父控件抛 
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel(GET_KEYSTATE_WPARAM(wParam),GET_WHEEL_DELTA_WPARAM(wParam),point);
		message_handled = TRUE;	//WM_MOUSEWHEEL  无需往父控件抛
		break;
	case WM_MOUSEMOVE:
		message_handled =  OnMouseMove(flag,point);
		break;					
	case WM_LBUTTONDOWN:
		message_handled = OnLButtonDown(flag,point);
		break;
	case WM_LBUTTONUP:
		message_handled = OnLButtonUp(flag,point);
		break;
	case WM_LBUTTONDBLCLK:
		message_handled = OnLButtonDoubleClicked(flag,point);
		break;
	case WM_RBUTTONDOWN:
		message_handled = OnRButtonDown(flag,point);
		break;
	case WM_RBUTTONUP:
		message_handled = OnRButtonUp(flag,point);
		break;
	case WM_RBUTTONDBLCLK:
		message_handled = OnRButtonDoubleClicked(flag,point);
		break;
	case WM_MBUTTONDOWN:
		message_handled = OnMButtonDown(flag,point);
		break;
	case WM_MBUTTONUP:
		message_handled = OnMButtonUp(flag,point);
		break;
	case WM_MBUTTONDBLCLK:
		message_handled = OnMButtonDoubleClicked(flag,point);
		break;
	}


	return message_handled;
}

void	UIControl::OnMouseEntered(UINT flag,const UIPoint &point)
{

}

void	UIControl::OnMouseExited(UINT flag,const UIPoint &point)
{

}

BOOL	UIControl::OnLButtonDown(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnLButtonUp(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnLButtonDoubleClicked(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnRButtonDown(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnRButtonUp(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnRButtonDoubleClicked(UINT flag,const UIPoint &point)
{
	return FALSE;
}


BOOL	UIControl::OnMButtonDown(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnMButtonUp(UINT flag,const UIPoint &point)
{
	return FALSE;
}

BOOL	UIControl::OnMButtonDoubleClicked(UINT flag,const UIPoint &point)
{
	return FALSE;
}

void	UIControl::OnMouseWheel(UINT flag, short delta,const UIPoint &point)
{
	
}

BOOL	UIControl::OnMouseMove(UINT flag,const UIPoint &point)
{
	return TRUE;
}


/////////////////////////////////////私有方法/////////////////////////////////////
void	UIControl::Arrange(const UIRect * parent_frame)
{
	ArrangeSelf(parent_frame);
	ArrangeChildren(&frame_);
}

void	UIControl::ArrangeChildren(const UIRect *parent_frame)
{
	for (size_t i = 0; i < children_.size(); i++)
	{
		children_[i]->Arrange(parent_frame);
	}
}

void	UIControl::SetParentWin(UIWindow *window)
{
	PTR_VOID(window);
	parent_win_ = window;
}

void	UIControl::SetParentVisibleRecursive(BOOL visible)
{
	parent_visible_ = visible;

	for (size_t i = 0; i < children_.size(); i++)
	{
		children_[i]->SetParentVisibleRecursive(visible);
	}
}

void	UIControl::SetParentEnabledRecursive(BOOL enabled)
{
	parent_enabled_ = enabled;

	for (size_t i = 0; i < children_.size(); i++)
	{
		children_[i]->SetParentEnabledRecursive(enabled);
	}
}


BOOL	UIControl::IsMouseInControl(const UIPoint &point)
{
	return ::PtInRect(&frame_,point);
}

void	UIControl::DispatchMouseMessage(UINT message,WPARAM wParam,LPARAM lParam)
{
	if (OnMouseMessage(message,wParam,lParam) == FALSE)
	{
		UIControl *control = GetParent();
		if (control)
		{
			control->DispatchMouseMessage(message,wParam,lParam);
		}
	}
}

Alignment	UIControl::GetAlignmentByString(const char *value)
{
	Alignment alignment = kAlignmentLeftTop;

	static BOOL init_alignment_list = FALSE;
	static std::vector<std::pair<const char *,Alignment>> alignments;

	if (!init_alignment_list)
	{
		alignments.push_back(std::make_pair("left_top",kAlignmentLeftTop));
		alignments.push_back(std::make_pair("left_center",kAlignmentLeftCenter));
		alignments.push_back(std::make_pair("left_bottom",kAlignmentLeftBottom));
		alignments.push_back(std::make_pair("center_top",kAlignmentCenterTop));
		alignments.push_back(std::make_pair("center",kAlignmentCenter));
		alignments.push_back(std::make_pair("center_bottom",kAlignmentCenterBottom));
		alignments.push_back(std::make_pair("right_top",kAlignmentRightTop));
		alignments.push_back(std::make_pair("right_center",kAlignmentRightCenter));
		alignments.push_back(std::make_pair("right_bottom",kAlignmentRightBottom));
		alignments.push_back(std::make_pair("left",kAlignmentLeft));
		alignments.push_back(std::make_pair("right",kAlignmentRight));
		alignments.push_back(std::make_pair("top",kAlignmentTop));
		alignments.push_back(std::make_pair("bottom",kAlignmentBottom));
		alignments.push_back(std::make_pair("fill",kAlignmentFill));
		init_alignment_list = TRUE;
	}

	for (size_t i = 0; i < alignments.size(); i++)
	{
		std::pair<const char *,Alignment> &pair = alignments[i];
		if(strcmp(pair.first,value) == 0)
		{
			alignment = pair.second;
			break;
		}
	}
	return alignment;
}

void	UIControl::SendNotify(UINotifyEvent event)
{
	UIWindow *window = GetParentWin();
	if (window)
	{
		window->FireEvent(event,this);
	}
}