#include "synEnvelopeInput.hpp"

synEnvelopeInput::synEnvelopeInput(wxWindow* parent, wxWindowID id, Envelope** c_destination, std::string c_title, wxPoint position)
:synSignalInput(parent, id, destination, c_title, position), destination{c_destination} {
}

void synEnvelopeInput::insert(std::string name, Signal* component) {
	if(auto buffer = dynamic_cast<Envelope*>(component)) {
		components.insert({name, buffer});
		choice->Append(name);
	}
}

void synEnvelopeInput::erase(std::string name) {
	bool is_set = false;
	if(*destination == components.at(name))
		is_set = true;
	components.erase(name);
	choice->Delete(choice->FindString(name));
	if(is_set)
		*destination = components.begin()->second;
}

void synEnvelopeInput::OnChoice(wxCommandEvent& event) {
	*destination = components.at(event.GetString().ToStdString());
	event.Skip();
}
