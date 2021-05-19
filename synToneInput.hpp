#pragma once

#include "synSignalInput.hpp"

#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include "../Synthall/Synthall"

class synToneInput :public synSignalInput {
	std::map<std::string, Tone*> components;
	Tone** destination;
public:
	synToneInput(wxWindow* parent, wxWindowID, Tone** destination, std::string c_title, wxPoint position = wxDefaultPosition);

	void insert(std::string, Signal*);
	void erase(std::string);
	void OnChoice(wxCommandEvent&);
};
