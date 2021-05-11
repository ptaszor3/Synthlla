#pragma once
#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include "../Synthall/Synthall"

template<class InputType>
class synInput :public wxChoice {
	std::map<std::string, InputType*> components;
	InputType** destination;
public:
	synInput(wxWindow* parent, wxWindowID, InputType** destination, wxPoint position = wxDefaultPosition, wxSize = wxDefaultSize);

	void insert(std::string, InputType*);
	void erase(std::string);
	void OnChoice(wxCommandEvent&);
};
