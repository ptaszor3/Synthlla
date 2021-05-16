#include "synEffectInput.hpp"

#include <algorithm>

template class synEffectInput<SingleSampleEffect>;
template class synEffectInput<WholeSampleEffect>;

template<class EffectType>
synEffectInput<EffectType>::synEffectInput(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position, wxSize size)
:wxChoice{parent, id, position, size}, destination{c_destination}, position{0} {
	Bind(wxEVT_CHOICE, &synEffectInput::OnChoice, this, wxID_ANY);
}

template<>
synEffectInput<SingleSampleEffect>::~synEffectInput() {
	if(*last_effect) {
		destination->single_sample_effects.erase(last_effect);
	}
}

template<>
synEffectInput<WholeSampleEffect>::~synEffectInput() {
	if(*last_effect) {
		destination->whole_sample_effects.erase(last_effect);
	}
}

template<class EffectType>
void synEffectInput<EffectType>::insert(std::string name,EffectType* effect) {
	bool is_there = false;
	try { 
		effects.at(name);
		is_there = true;
	}
	catch(...){}

	if(!is_there) {
		effects.insert({name, effect});
		Append(name);
	}
	else
		throw(NameHasAlreadyBeenInserted_exception());
}

template<>
void synEffectInput<SingleSampleEffect>::erase(std::string name) {
	decltype(destination->single_sample_effects.begin()) iterator_to_element_getting_erased;
	if((iterator_to_element_getting_erased = std::find(destination->single_sample_effects.begin(), destination->single_sample_effects.end(), effects.at(name))) != destination->single_sample_effects.end());
		destination->single_sample_effects.erase(iterator_to_element_getting_erased);
	effects.erase(name);
	Delete(FindString(name));
}

template<>
void synEffectInput<WholeSampleEffect>::erase(std::string name) {
	decltype(destination->whole_sample_effects.begin()) iterator_to_element_getting_erased;
	if((iterator_to_element_getting_erased = std::find(destination->whole_sample_effects.begin(), destination->whole_sample_effects.end(), effects.at(name))) != destination->whole_sample_effects.end());
		destination->whole_sample_effects.erase(iterator_to_element_getting_erased);
	effects.erase(name);
	Delete(FindString(name));
}

template<>
void synEffectInput<SingleSampleEffect>::move_up() {
	if(position == 0)
		throw CannotGoHigher_exception();
	SingleSampleEffect* effect_buffer = destination->single_sample_effects[position];
	destination->single_sample_effects.erase(last_effect--);
	destination->single_sample_effects.insert(destination->single_sample_effects.begin() + --position, effect_buffer);
}

template<>
void synEffectInput<WholeSampleEffect>::move_up() {
	if(position == 0)
		throw CannotGoHigher_exception();
	WholeSampleEffect* effect_buffer = destination->whole_sample_effects[position];
	destination->whole_sample_effects.erase(last_effect--);
	destination->whole_sample_effects.insert(destination->whole_sample_effects.begin() + --position, effect_buffer);
}

template<>
void synEffectInput<SingleSampleEffect>::move_down() {
	if(destination->single_sample_effects.begin() + position >= destination->single_sample_effects.end())
		throw CannotGoLower_exception();
	SingleSampleEffect* effect_buffer = destination->single_sample_effects[position];
	destination->single_sample_effects.erase(last_effect++);
	destination->single_sample_effects.insert(destination->single_sample_effects.begin() + ++position, effect_buffer);
}

template<>
void synEffectInput<WholeSampleEffect>::move_down() {
	if(destination->whole_sample_effects.begin() + position >= destination->whole_sample_effects.end())
		throw CannotGoLower_exception();
	WholeSampleEffect* effect_buffer = destination->whole_sample_effects[position];
	destination->whole_sample_effects.erase(last_effect++);
	destination->whole_sample_effects.insert(destination->whole_sample_effects.begin() + ++position, effect_buffer);
}

template<>
void synEffectInput<SingleSampleEffect>::OnChoice(wxCommandEvent& event) {
	if(is_set) {
		destination->single_sample_effects.erase(std::find(destination->single_sample_effects.begin(), destination->single_sample_effects.end(), *last_effect));
	}

	last_effect = destination->single_sample_effects.insert(destination->single_sample_effects.begin() + position, effects.at(event.GetString().ToStdString()));
	is_set = true;
	event.Skip();
}

template<class WholeSampleEffect>
void synEffectInput<WholeSampleEffect>::OnChoice(wxCommandEvent& event) {
	if(is_set) {
		destination->whole_sample_effects.erase(std::find(destination->whole_sample_effects.begin(), destination->whole_sample_effects.end(), *last_effect));
	}

	last_effect = destination->whole_sample_effects.insert(destination->whole_sample_effects.begin() + position, effects.at(event.GetString().ToStdString()));
	is_set = true;
	event.Skip();
}
