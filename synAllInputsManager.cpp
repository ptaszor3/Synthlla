#include "synAllInputsManager.hpp"

void synAllInputsManager::insert(std::string name, Signal* output) {
	signals.insert(name, output);
}

void synAllInputsManager::erase_signal(std::string name) {
	signals.erase(name);
}

synSignalInput* synAllInputsManager::get_new_signal_input(wxWindow* parent, wxWindowID id, Signal** destination, wxPoint position, wxSize size) {
	return signals.get_new_input(parent, id, destination, position, size);
}

void synAllInputsManager::free_input(synSignalInput* input) {
	signals.free(input);
}
