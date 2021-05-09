#pragma once
#include "synSignalInput.hpp"

#include "../Synthall/Synthall"
#include <wx/wx.h>
#include <map>
#include <vector>
#include <string>

/*class synSynItems {
	std::map<std::string, Signal*> signals;
	std::map<std::string, WholeSampleEffect*> whole_sample_effects;
	std::map<std::string, SingleSampleEffect*> single_sample_effects;

	std::map<unsigned int, synSignalInput*> destinations;
	unsigned int last_destinations_id = 0;

public:
	void append_signal(std::string name, Signal* signal) {
		signals.insert({name, signal});
	}
	void append_whole_sample_effect(std::string name, WholeSampleEffect* effect) {
		whole_sample_effects.insert({name, effect});
	}
	void append_single_sample_effect(std::string name, SingleSampleEffect* effect) {
		single_sample_effect.insert({name, effect});
	}

	void remove_signal(std::string name) {
		signals.erase(name);
	}
	void remove_whole_sample_effect(std::string name) {
		whole_sample_effects.erase(name);
	}
	void remove_single_sample_effect(std::string name) {
		single_sample_effects.erase(name);
	}

	synSignalInput get_new_signal_choice_box(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size) {
		destinations.insert(last_destinations_id++, new synSignalInput(parent, id, position, size));
		for()
			destinations.at(last_destinations_id)
		return destinations.at(last_destinations_id);
	}
};*/
