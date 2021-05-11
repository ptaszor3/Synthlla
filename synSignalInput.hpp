#pragma once
#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include "../Synthall/Synthall"

class synSignalInput :public wxChoice {
	std::map<std::string, Signal*> components;
	Signal** destination;
public:
	synSignalInput(wxWindow* parent, wxWindowID, Signal** destination, wxPoint position = wxDefaultPosition, wxSize = wxDefaultSize);

	void insert(std::string, Signal*);
	void erase(std::string);
	void OnChoice(wxCommandEvent&);
};
