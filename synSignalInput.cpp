#include "synSignalInput.hpp"

synSignalInput::synSignalInput(wxWindow* parent, wxWindowID id, Signal** c_destination, std::string c_title, wxPoint position)
:wxWindow{parent, id, position, {230, 75}, wxBORDER_THEME}, destination{c_destination} {
	title = new wxStaticText(this, wxID_ANY, c_title, {15, 5}, {-1, 15});
	choice = new wxChoice(this, wxID_ANY, {15, 30}, {200, 30});
	
	Bind(wxEVT_CHOICE, &synSignalInput::OnChoice, this, wxID_ANY);
}

void synSignalInput::insert(std::string name, Signal* component) {
	components.insert({name, component});
	choice->Append(name);
}

void synSignalInput::erase(std::string name) {
	bool is_set = false;
	if(*destination == components.at(name))
		is_set = true;
	components.erase(name);
	choice->Delete(choice->FindString(name));
	if(is_set)
		*destination = components.begin()->second;
}

void synSignalInput::OnChoice(wxCommandEvent& event) {
	*destination = components.at(event.GetString().ToStdString());
	event.Skip();
}
