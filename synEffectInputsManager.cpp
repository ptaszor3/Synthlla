#include "synEffectInputsManager.hpp"

void synEffectInputsManager::insert(std::string name, SingleSampleEffect* effect) {
	bool is_there = false;
	try { 
		single_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}

	if(!is_there) {
		single_sample_effects.insert({name, effect});
		for(auto& x : single_sample_inputs)
			x->insert(name, effect);
	}
	else
		throw(NameHasAlreadyBeenUsed_exception());
}

void synEffectInputsManager::insert(std::string name, WholeSampleEffect* effect) {
	bool is_there = false;
	try {
		whole_sample_effects.at(name);
		is_there = true;
	}
	catch(...) {}

	if(!is_there) {
		whole_sample_effects.insert({name, effect});
		for(auto& x : whole_sample_inputs)
			x->insert(name, effect);
	}
	else
		throw(NameHasAlreadyBeenUsed_exception());
}

void synEffectInputsManager::erase_single_sample_effect(std::string name) {
	single_sample_effects.erase(name);
	for(auto& x : single_sample_inputs)
		x->erase(name);
}

void synEffectInputsManager::erase_whole_sample_effect(std::string name) {
	whole_sample_effects.erase(name);
	for(auto& x : whole_sample_inputs)
		x->erase(name);
}

synEffectInput<SingleSampleEffect>* synEffectInputsManager::get_new_single_sample_input(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position, wxSize size) {
	synEffectInput<SingleSampleEffect>* buffer = new synEffectInput<SingleSampleEffect>(parent, id, c_destination, position, size);
	for(auto& x : single_sample_effects)
		buffer->insert(x.first, x.second);
	single_sample_inputs.insert(buffer);
	return buffer;
}

synEffectInput<WholeSampleEffect>* synEffectInputsManager::get_new_whole_sample_input(wxWindow* parent, wxWindowID id, Instrument* c_destination, wxPoint position, wxSize size) {
	synEffectInput<WholeSampleEffect>* buffer = new synEffectInput<WholeSampleEffect>(parent, id, c_destination, position, size);
	for(auto& x : whole_sample_effects)
		buffer->insert(x.first, x.second);
	whole_sample_inputs.insert(buffer);
	return buffer;
}

void synEffectInputsManager::free_input(synEffectInput<SingleSampleEffect>* to_be_freed) {
	single_sample_inputs.erase(to_be_freed);
	delete to_be_freed;
}

void synEffectInputsManager::free_input(synEffectInput<WholeSampleEffect>* to_be_freed) {
	whole_sample_inputs.erase(to_be_freed);
	delete to_be_freed;
}
