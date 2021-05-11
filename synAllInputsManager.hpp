#pragma once 
#include "synSignalInputsManager.hpp"

#include <unordered_set>

class synAllInputsManager {
	synSignalInputsManager signals;

public:
	void insert(std::string name, Signal* output);
	void erase_signal(std::string name);
	synSignalInput* get_new_signal_input(wxWindow*, wxWindowID, Signal**, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	void free_input(synSignalInput*);
};
