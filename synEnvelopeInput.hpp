#pragma once

#include "synSignalInput.hpp"

#include <wx/wx.h>
#include <map>
#include <utility>
#include <string>
#include "../Synthall/Synthall"

class synEnvelopeInput :public synSignalInput {
	std::map<std::string, Envelope*> components;
	Envelope** destination;
public:
	synEnvelopeInput(wxWindow* parent, wxWindowID, Envelope** destination, std::string c_title, wxPoint position = wxDefaultPosition);

	void insert(std::string, Signal*);
	void erase(std::string);
	void OnChoice(wxCommandEvent&);
};
