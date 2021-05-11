#include "synEffectInput.hpp"

#include <algorithm>

synEffectInput::synEffectInput(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position, wxSize size)
:wxChoice{parent, id, position, size}, destination{c_destination} {
	Bind(wxEVT_CHOICE, &synEffectInput::OnChoice, this, wxID_ANY);
}

void synEffectInput::insert(std::string name, SingleSampleEffect* effect) {
	single_sample_effects.insert({name, effect});
	Append(name);
}

void synEffectInput::insert(std::string name, WholeSampleEffect* effect) {
	whole_sample_effects.insert({name, effect});
	Append(name);
}

void synEffectInput::erase_single_sample_effect(std::string name) {
	decltype(destination->single_sample_effects.begin()) iterator_to_element_getting_erased;
	if((iterator_to_element_getting_erased = std::find(destination->single_sample_effects.begin(), destination->single_sample_effects.end(), single_sample_effects.at(name))) != destination->single_sample_effects.end());
		destination->single_sample_effects.erase(iterator_to_element_getting_erased);
	single_sample_effects.erase(name);
	Delete(FindString(name));
}

void synEffectInput::erase_whole_sample_effect(std::string name) {
	decltype(destination->whole_sample_effects.begin()) iterator_to_element_getting_erased;
	if((iterator_to_element_getting_erased = std::find(destination->whole_sample_effects.begin(), destination->whole_sample_effects.end(), whole_sample_effects.at(name))) != destination->whole_sample_effects.end());
		destination->whole_sample_effects.erase(iterator_to_element_getting_erased);
	whole_sample_effects.erase(name);
	Delete(FindString(name));
}

void synEffectInput::OnChoice(wxCommandEvent& event) {
	if(last_choice_type != NONE) {
		switch(last_choice_type) {
			case SINGLE_SAMPLE_EFFECT:
				destination->single_sample_effects.erase(std::find(destination->single_sample_effects.begin(), destination->single_sample_effects.end(), last.single_sample_effect));
			break;
			case WHOLE_SAMPLE_EFFECT:
				destination->whole_sample_effects.erase(std::find(destination->whole_sample_effects.begin(), destination->whole_sample_effects.end(), last.whole_sample_effect));
			break;
		}
	}

	try {
		destination->single_sample_effects.push_back(single_sample_effects.at(event.GetString().ToStdString()));
	}
	catch(...) {}
	try {
		destination->whole_sample_effects.push_back(whole_sample_effects.at(event.GetString().ToStdString()));
	}
	catch(...) {}
	event.Skip();
}
