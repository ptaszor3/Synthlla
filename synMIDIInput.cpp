#include "synMIDIInput.hpp"

synMIDIInput::synMIDIInput(wxWindow* parent, wxWindowID id, Instrument* c_instrument, wxPoint position, wxSize size) 
:wxWindow(parent, id, position, size), inputs::MIDIInput{c_instrument} {
	text = new wxStaticText{this, wxID_ANY, "Midi input", wxPoint{15, 5}};
	choice = new wxChoice{this, wxID_ANY, wxPoint(15, 25)};
	refresh = new wxButton{this, wxID_ANY, "Refresh", wxPoint{300, 25}};

	update();
}

void synMIDIInput::OnChoice(wxCommandEvent& event) {
	disconnect();
	connect(ids.at(event.GetString().ToStdString()));
}

void synMIDIInput::OnButton(wxCommandEvent& event) {
	update();
}

void synMIDIInput::update() {
	ids.clear();
	ids = inputs::MIDIInput::get_all_inputs();

	std::string last_selection;

	if(choice->GetSelection() != wxNOT_FOUND)
		last_selection = choice->GetString(choice->GetSelection());
	else
		last_selection = "";

	bool is_there_last_selection{false};
	choice->Clear();
	for(auto x : ids) {
		choice->Append(x.first);
		if(x.first == last_selection) {
			is_there_last_selection = true;
		}
	}
	if(is_there_last_selection)
		choice->SetStringSelection(last_selection);
	else
		disconnect();
}

wxBEGIN_EVENT_TABLE(synMIDIInput, wxWindow)
	EVT_BUTTON(wxID_ANY, synMIDIInput::OnButton)
	EVT_CHOICE(wxID_ANY, synMIDIInput::OnChoice)
wxEND_EVENT_TABLE()
