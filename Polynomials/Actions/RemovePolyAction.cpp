
#include "RemovePolyAction.h"
#include "..\\PolynomialsApplication.h"

IAction * RemovePolyAction::clone()
{
	RemovePolyAction * result = new RemovePolyAction();
	result->actionContext = this->actionContext;
	return result;
}

void RemovePolyAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();

	// Cannot fucking set const wchar* into out wchar*, so copy it manually...
	std::wstring str = std::wstring(list->GetItemText(actionContext.getSelectedPolyIndex(), 0).GetString());
	size_t length = str.length();
	text = new WCHAR[length + 1]{ 0 };
	for (int i = 0; i < length; i++) {
		text[i] = str[i];
	}

	list->DeleteItem(actionContext.getSelectedPolyIndex());

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void RemovePolyAction::undo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->InsertItem(actionContext.getSelectedPolyIndex(), text);

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}

void RemovePolyAction::redo()
{
	CListCtrl * list = PolynomialsApplication::getInstance().getPolyListControl();
	list->DeleteItem(actionContext.getSelectedPolyIndex());

	// Refresh the width. We do this in case there is a vertical scrollbar created, that adds some 
	// pixels to the width of the list, which results in a horizontal scrollbar.
	list->SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}