#include "synEffectRepresentation.hpp"

wxDEFINE_EVENT(SYN_EFFECT_UP, wxCommandEvent);
wxDEFINE_EVENT(SYN_EFFECT_DOWN, wxCommandEvent);
wxDEFINE_EVENT(SYN_EFFECT_REMOVE, wxCommandEvent);

synEffectRepresentation::synEffectRepresentation(wxWindow* parent, wxWindowID id, std::string c_title, wxPoint position, wxSize size)
:wxWindow(parent, id, position, {235, 115}, wxBORDER_THEME) {
	title = new wxStaticText(this, wxID_ANY, c_title, wxPoint(15, 15), wxSize(-1, 15));
	up = new wxButton(this, 1, "Move up", wxPoint(15, 40), wxSize(90, 30));
	down = new wxButton(this, 2, "Move down", wxPoint(15, 70), wxSize(90, 30));
	remove = new wxButton(this, 3, "Remove", wxPoint(130, 55), wxSize(90, 30));
}

void synEffectRepresentation::OnUp(wxCommandEvent& old_event) {
	wxCommandEvent event(SYN_EFFECT_UP, GetId());
	event.SetEventObject(this);
	event.SetId(this->GetId());
	ProcessWindowEvent(event);
	old_event.Skip();
}

void synEffectRepresentation::OnDown(wxCommandEvent& old_event) {
	wxCommandEvent event(SYN_EFFECT_DOWN, GetId());
	event.SetEventObject(this);
	event.SetId(this->GetId());
	ProcessWindowEvent(event);
	old_event.Skip();
}

void synEffectRepresentation::OnRemove(wxCommandEvent& old_event) {
	wxCommandEvent event(SYN_EFFECT_REMOVE, GetId());
	event.SetEventObject(this);
	event.SetId(this->GetId());
	ProcessWindowEvent(event);
	old_event.Skip();
}

wxBEGIN_EVENT_TABLE(synEffectRepresentation, wxWindow)
	EVT_BUTTON(1, synEffectRepresentation::OnUp)
	EVT_BUTTON(2, synEffectRepresentation::OnDown)
	EVT_BUTTON(3, synEffectRepresentation::OnRemove)
wxEND_EVENT_TABLE()
