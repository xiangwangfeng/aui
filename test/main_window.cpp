#include "main_window.h"
#include "util.h"


UIButtonConfig *GetDefaultButtonConfig()
{
	static UIButtonConfig *config = NULL;
	if (!config)
	{
		config = new UIButtonConfig();
		config->text_disable_color_ = RGB(163,163,163);
		config->text_normal_color_	= RGB(0,0,0);
		config->text_focus_color_	= RGB(0,0,0);
		config->normal_image_		= Util::GetAppPath() + L"/resources/common_normal.png";
		config->hover_image_		= Util::GetAppPath() + L"/resources/common_hover.png";	
		config->pressed_image_		= Util::GetAppPath() +  L"/resources/common_pressed.png";
		config->disabled_image_		= Util::GetAppPath() +  L"/resources/common_disable.png";
	}
	return config;
}

UILableConfig *GetDefaultLabelConfig()
{
	static UILableConfig *config = NULL;
	if (!config)
	{
		config = new UILableConfig();
	}
	return config;
}



BOOL	MainWindow::AfterCreated()
{
	SetIcon((Util::GetAppPath() + L"/resources/icon/amao.ico").c_str());
	CreateControls();
	AddNotifier(this);
	return TRUE;
}


void	MainWindow::Notify(UINotifyEvent event,UIControl *control)
{
	if (control->GetTag() == 5 && event == kEventTextChanged)
	{
		UIEdit *edit = (UIEdit *)control;
		current_label_->SetText(edit->GetEditText());
	}
}

void	MainWindow::CreateControls()
{
	UIControl *root_control = new UIControl();
	AddRootControl(root_control);

	UIEdit *edit = new UIEdit();
	edit->SetSize(200,24);
	edit->SetMargin(0,20);
	edit->SetAlignmentType(kAlignmentCenterTop);
	edit->SetTag(5);
	root_control->AddSubControl(edit);


	UILabel *url_label = new UILabel();
	url_label->SetSize(200,40);
	url_label->SetMargin(0,70);
	url_label->SetAlignmentType(kAlignmentCenterTop);
	url_label->LoadConfig(*GetDefaultLabelConfig());
	url_label->SetText(L"我是一个Label，你信么？");
	url_label->SetURL(L"www.163.com");
	current_label_ = url_label;
	root_control->AddSubControl(url_label);

	UIButton *open_yxsg_button = new UIButton();
	open_yxsg_button->SetSize(100,40);
	open_yxsg_button->SetMargin(0,130);
	open_yxsg_button->SetAlignmentType(kAlignmentCenterTop);
	open_yxsg_button->LoadButtonConfig(*GetDefaultButtonConfig());
	open_yxsg_button->SetText(L"英雄三国");
	root_control->AddSubControl(open_yxsg_button);
}