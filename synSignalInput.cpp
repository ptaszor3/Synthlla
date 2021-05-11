#include "synSignalInput.hpp"

synSignalInput::synSignalInput(wxWindow* parent, wxWindowID id, Signal** c_destination, wxPoint position, wxSize size)
:wxChoice{parent, id, position, size}, destination{c_destination} {
	Bind(wxEVT_CHOICE, &synSignalInput::OnChoice, this, wxID_ANY);
}

void synSignalInput::insert(std::string name, Signal* component) {
	components.insert({name, component});
	Append(name);
}

void synSignalInput::erase(std::string name) {
	bool is_set = false;
	if(*destination == components.at(name))
		is_set = true;
	components.erase(name);
	Delete(FindString(name));
	if(is_set)
		*destination = components.begin()->second;
}

void synSignalInput::OnChoice(wxCommandEvent& event) {
	*destination = components.at(event.GetString().ToStdString());
	event.Skip();
}
