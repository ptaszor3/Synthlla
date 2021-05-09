#include "synSignalInput.hpp"

template<class InputType>
synSignalInput<InputType>::synSignalInput(wxWindow* parent, wxWindowID id, InputType** c_destination, wxPoint position, wxSize size)
:wxChoice{parent, id, position, size}, destination{c_destination} {
	Bind(wxEVT_CHOICE, &synSignalInput<InputType>::OnChoice, this, wxID_ANY);
}

template<class InputType>
void synSignalInput<InputType>::add_signal(std::string name, InputType* signal) {
	signals.insert({name, signal});
	Append(name);
}

template<class InputType>
void synSignalInput<InputType>::remove_signal(std::string name) {
	signals.erase(name);
	Delete(FindString(name));
}

template<class InputType>
void synSignalInput<InputType>::OnChoice(wxCommandEvent& event) {
	*destination = signals.at(event.GetString().ToStdString());
	event.Skip();
}

template class synSignalInput<Signal>;
template class synSignalInput<SingleSampleEffect>;
template class synSignalInput<WholeSampleEffect>;

/*wxBEGIN_EVENT_TABLE(synSignalInput<InputType>, wxChoice) 
	EVT_CHOICE(wxID_ANY, synSignalInput<InputType>::OnChoice)
wxEND_EVENT_TABLE()*/
