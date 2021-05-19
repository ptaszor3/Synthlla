#pragma once
#include "synSignalInput.hpp"
#include "synToneInput.hpp"
#include "synEnvelopeInput.hpp"

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
	synSignalInput* get_new_signal_input(wxWindow*, wxWindowID, Signal** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	synToneInput* get_new_tone_input(wxWindow*, wxWindowID, Tone** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	synEnvelopeInput* get_new_envelope_input(wxWindow*, wxWindowID, Envelope** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	void free_input(synSignalInput*);
};
