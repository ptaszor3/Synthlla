#pragma once
#include "synSignalInput.hpp"

#include <string>
#include <map>
#include <vector>
#include <unordered_set>

class synSignalInputsManager {
	std::map<std::string, Signal*> outputs;
	std::unordered_set<synSignalInput*> inputs;

	Signal* const default_signal = new tones::basic::Sin();
public:
	Signal* get_default_signal(){
		return default_signal;
	}
	void insert(std::string, Signal*);
	void erase_signal(std::string);
	synSignalInput* get_new_input(wxWindow*, wxWindowID, Signal** destination, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	void free_input(synSignalInput*);
};
