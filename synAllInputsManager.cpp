#include "synAllInputsManager.hpp"

template<>
synInputsManager<Signal>* synAllInputsManager::get_set_of_type<Signal>() {
	return &signals;
}

template<>
synInputsManager<SingleSampleEffect>* synAllInputsManager::get_set_of_type<SingleSampleEffect>() {
	return &single_sample_effects;
}

template<>
synInputsManager<WholeSampleEffect>* synAllInputsManager::get_set_of_type<WholeSampleEffect>() {
	return &whole_sample_effects;
}

template<class InputType>
void synAllInputsManager::insert(std::string name, InputType* output) {
	get_set_of_type<InputType>()->insert(name, output);
}

template void synAllInputsManager::insert<Signal>(std::string, Signal*);
template void synAllInputsManager::insert<SingleSampleEffect>(std::string, SingleSampleEffect*);
template void synAllInputsManager::insert<WholeSampleEffect>(std::string, WholeSampleEffect*);

template<class InputType>
void synAllInputsManager::erase(std::string name) {
	get_set_of_type<InputType>()->erase(name);
}

template void synAllInputsManager::erase<Signal>(std::string);
template void synAllInputsManager::erase<SingleSampleEffect>(std::string);
template void synAllInputsManager::erase<WholeSampleEffect>(std::string);

template<class InputType>
synInput<InputType>* synAllInputsManager::get_new_input(wxWindow* parent, wxWindowID id, InputType** destination, wxPoint position, wxSize size) {
	return get_set_of_type<InputType>()->get_new_input(parent, id, destination, position, size);
}

template synInput<Signal>* synAllInputsManager::get_new_input(wxWindow* parent, wxWindowID id,Signal**, wxPoint, wxSize);
template synInput<SingleSampleEffect>* synAllInputsManager::get_new_input(wxWindow* parent, wxWindowID id,SingleSampleEffect**, wxPoint, wxSize);
template synInput<WholeSampleEffect>* synAllInputsManager::get_new_input(wxWindow* parent, wxWindowID id,WholeSampleEffect**, wxPoint, wxSize);

template<class InputType>
void synAllInputsManager::free_input(synInput<InputType>* input) {
	get_set_of_type<InputType>()->free(input);
}

template void synAllInputsManager::free_input<Signal>(synInput<Signal>* input);
template void synAllInputsManager::free_input<SingleSampleEffect>(synInput<SingleSampleEffect>* input);
template void synAllInputsManager::free_input<WholeSampleEffect>(synInput<WholeSampleEffect>* input);
