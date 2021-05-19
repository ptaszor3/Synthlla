#pragma once
#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include <typeinfo>
#include "../Synthall/Synthall"

class synSignalInput :public wxWindow {
protected:
	std::map<std::string, Signal*> components;
	Signal** destination;
	wxStaticText* title;
	wxChoice* choice;
public:
	synSignalInput(wxWindow* parent, wxWindowID, Signal** destination, std::string c_title, wxPoint position = wxDefaultPosition);
	virtual ~synSignalInput() = default;

	virtual void insert(std::string, Signal*);
	virtual void erase(std::string);
	virtual void OnChoice(wxCommandEvent&);
};
