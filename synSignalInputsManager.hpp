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
	Envelope* const default_envelope = new envelopes::basic::NoEnvelope();
public:
	Signal* get_default_signal() {
		return default_signal;
	}
	Tone* get_default_tone() {
		return dynamic_cast<Tone*>(default_signal);
	}
	Envelope* get_default_envelope() {
		return default_envelope;
	}
	void insert(std::string, Signal*);
	void erase_signal(std::string);
	synSignalInput* get_new_signal_input(wxWindow*, wxWindowID, Signal** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	synToneInput* get_new_tone_input(wxWindow*, wxWindowID, Tone** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	synEnvelopeInput* get_new_envelope_input(wxWindow*, wxWindowID, Envelope** destination, std::string c_title, wxPoint = wxDefaultPosition, wxSize = wxDefaultSize);
	void free_input(synSignalInput*);
};
