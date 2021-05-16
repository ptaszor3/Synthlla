#pragma once

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <map>

class synMIDIInput :public wxWindow, private inputs::MIDIInput { 
	wxStaticText* text;
	wxChoice* choice;
	wxButton* refresh;
	std::map<std::string, int> ids;
public:
	synMIDIInput(wxWindow* parent, wxWindowID id, Instrument* c_instrument, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize);

	void OnChoice(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);

	void update();

	wxDECLARE_EVENT_TABLE();
};
