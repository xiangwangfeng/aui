#pragma once

#include "../aui/include/aui.h"

class MainWindow : public UIWindow, IUINotify
{
public:
	BOOL AfterCreated();

	void Notify(UINotifyEvent event,UIControl *control);

private:
	void CreateControls();
private:
	UILabel *current_label_;
};