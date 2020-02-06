#pragma once

namespace rescan
{
	class SelectionMenu;

	struct SelectionMenuCallback
	{
		virtual ~SelectionMenuCallback() {};
		virtual void EnterClicked(SelectionMenu* sender) = 0;
	};
}