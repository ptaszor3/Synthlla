#include "synInput.hpp"

template<class InputType>
synInput<InputType>::synInput(wxWindow* parent, wxWindowID id, InputType** c_destination, wxPoint position, wxSize size)
:wxChoice{parent, id, position, size}, destination{c_destination} {
	Bind(wxEVT_CHOICE, &synInput<InputType>::OnChoice, this, wxID_ANY);
}

template<class InputType>
void synInput<InputType>::insert(std::string name, InputType* component) {
	components.insert({name, component});
	Append(name);
}

template<class InputType>
void synInput<InputType>::erase(std::string name) {
	components.erase(name);
	Delete(FindString(name));
}

template<class InputType>
void synInput<InputType>::OnChoice(wxCommandEvent& event) {
	*destination = components.at(event.GetString().ToStdString());
	event.Skip();
}

template class synInput<Signal>;
template class synInput<SingleSampleEffect>;
template class synInput<WholeSampleEffect>;
