#include "synToneInput.hpp"

#warning iostream only for debug
#include <iostream>

synToneInput::synToneInput(wxWindow* parent, wxWindowID id, Tone** c_destination, std::string c_title, wxPoint position)
:synSignalInput(parent, id, destination, c_title, position), destination{c_destination} {}

void synToneInput::insert(std::string name, Signal* component) {
	if(auto buffer = dynamic_cast<Tone*>(component)) {
		components.insert({name, buffer});
		choice->Append(name);
	}
}

void synToneInput::erase(std::string name) {
	bool is_set = false;
	if(*destination == components.at(name))
		is_set = true;
	components.erase(name);
	choice->Delete(choice->FindString(name));
	if(is_set)
		*destination = components.begin()->second;
}

void synToneInput::OnChoice(wxCommandEvent& event) {
	*destination = components.at(event.GetString().ToStdString());
	event.Skip();
}
