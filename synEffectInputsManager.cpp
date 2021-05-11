#include "synEffectInputsManager.hpp"

void synEffectInputsManager::insert(std::string name, SingleSampleEffect* effect) {
	bool is_there = false;
	try { 
		single_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}
	try {
		whole_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}

	if(!is_there) {
		single_sample_effects.insert({name, effect});
		for(auto& x : inputs)
			x->insert(name, effect);
	}
	else
		throw(NameHasAlreadyBeenUsed_exception());
}

void synEffectInputsManager::insert(std::string name, WholeSampleEffect* effect) {
	bool is_there = false;
	try { 
		single_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}
	try {
		whole_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}

	if(!is_there) {
		whole_sample_effects.insert({name, effect});
		for(auto& x : inputs)
			x->insert(name, effect);
	}
	else
		throw(NameHasAlreadyBeenUsed_exception());
}

void synEffectInputsManager::erase_single_sample_effect(std::string name) {
	single_sample_effects.erase(name);
	for(auto& x : inputs)
		x->erase_single_sample_effect(name);
}

void synEffectInputsManager::erase_whole_sample_effect(std::string name) {
	whole_sample_effects.erase(name);
	for(auto& x : inputs)
		x->erase_whole_sample_effect(name);
}

synEffectInput* synEffectInputsManager::get_new_input(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position, wxSize size) {
	synEffectInput* buffer = new synEffectInput(parent, id, c_destination, position, size);
	for(auto& x : single_sample_effects)
		buffer->insert(x.first, x.second);
	for(auto& x : whole_sample_effects)
		buffer->insert(x.first, x.second);
	inputs.insert(buffer);
	return buffer;
}

void synEffectInputsManager::free_input(synEffectInput* to_be_freed) {
	inputs.erase(to_be_freed);
	delete to_be_freed;
}
