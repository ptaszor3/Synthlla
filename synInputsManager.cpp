#include "synInputsManager.hpp"

template<class InputType>
void synInputsManager<InputType>::insert(std::string name, InputType* output) {
	outputs.insert({name, output});
	for(auto& x : inputs) 
		x->insert(name, output);
}

template<class InputType>
void synInputsManager<InputType>::erase(std::string name) {
	outputs.erase(name);
	for(auto& x : inputs)
		x->erase(name);
}

template<class InputType>
synInput<InputType>* synInputsManager<InputType>::get_new_input(wxWindow* parent, wxWindowID id, InputType** destination, wxPoint position, wxSize size) {
	auto new_input{new synInput<InputType>(parent, id, destination, position, size)};
	for(auto x : outputs)
		new_input->insert(x.first, x.second);
	inputs.insert(new_input);
	return new_input;
}

template<class InputType>
void synInputsManager<InputType>::free(synInput<InputType>* input_to_be_freed) {
	inputs.erase(input_to_be_freed);
	delete input_to_be_freed;
}

template class synInputsManager<Signal>;
template class synInputsManager<WholeSampleEffect>;
template class synInputsManager<SingleSampleEffect>;
