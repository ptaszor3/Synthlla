#pragma once

#include "../Synthall/Synthall"
#include <wx/wx.h>

class synSynchronization :public wxRadioBox {
	effects::SynchronizationType* synchronization_type;
public:
	synSynchronization(wxWindow* parent, wxWindowID id, effects::SynchronizationType* c_synchronization_type , wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize)
	:synchronization_type{c_synchronization_type} {
		wxArrayString choices;
		choices.Add("Synchronized");
		choices.Add("Unsynchronized");

		Create(parent, id, "Synchronization type", position, size, choices, 2, wxRA_VERTICAL);
	}

	void OnClicked(wxCommandEvent& event) {
		if(event.GetString() == _("Synchronized"))
			*synchronization_type = effects::SynchronizationType::Synchronized;
		else if(event.GetString() == _("Unsynchronized"))
			*synchronization_type = effects::SynchronizationType::Unsynchronized;
	}

	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(synSynchronization, wxRadioBox)
	EVT_RADIOBOX(wxID_ANY, synSynchronization::OnClicked)
wxEND_EVENT_TABLE()
