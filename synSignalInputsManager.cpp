#include "synSignalInputsManager.hpp"

void synSignalInputsManager::insert(std::string name, Signal* output) {
	outputs.insert({name, output});
	for(auto& x : inputs) 
		x->insert(name, output);
}

void synSignalInputsManager::erase_signal(std::string name) {
	outputs.erase(name);
	for(auto& x : inputs)
		x->erase(name);
}

synSignalInput* synSignalInputsManager::get_new_input(wxWindow* parent, wxWindowID id, Signal** destination, wxPoint position, wxSize size) {
	auto new_input{new synSignalInput(parent, id, destination, position, size)};
	for(auto x : outputs)
		new_input->insert(x.first, x.second);
	inputs.insert(new_input);
	return new_input;
}

void synSignalInputsManager::free_input(synSignalInput* input_to_be_freed) {
	inputs.erase(input_to_be_freed);
	delete input_to_be_freed;
}

