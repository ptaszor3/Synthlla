#pragma once

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <string>

wxDECLARE_EVENT(SYN_EFFECT_UP, wxCommandEvent);
wxDECLARE_EVENT(SYN_EFFECT_DOWN, wxCommandEvent);
wxDECLARE_EVENT(SYN_EFFECT_REMOVE, wxCommandEvent);

class synEffectRepresentation :public wxWindow {
	wxStaticText* title;
	wxButton* up;
	wxButton* down;
	wxButton* remove;
public:
	synEffectRepresentation(wxWindow* parent, wxWindowID id, std::string c_title, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);

	void OnUp(wxCommandEvent&);
	void OnDown(wxCommandEvent&);
	void OnRemove(wxCommandEvent&);

	wxDECLARE_EVENT_TABLE();
};
