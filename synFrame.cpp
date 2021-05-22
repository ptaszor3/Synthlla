#include "synFrame.hpp"

#include "synSlider.hpp"
#include "synARSD.hpp"
#include "synMIDIInput.hpp"
#include "synEffectContext.hpp"
#include "synInstrument.hpp"

#include "synQuadraticARSD.hpp"
#include "synRectangle.hpp"
#include "synVibrato.hpp"
#include "synTremolo.hpp"
#include "synSynchronizedVibrato.hpp"
#include "synUnsynchronizedVibrato.hpp"
#include "synEffectInputsManager.hpp"
#include "synSignalInputsManager.hpp"

#include <iostream>
#include <thread>

synSignalInputsManager signal_manager;
synEffectInputsManager effect_manager;

synFrame::synFrame(std::string title, wxPoint position, wxSize size) 
:wxFrame(nullptr, wxID_ANY, title, position, size) {

	wxMenuBar *menu_bar = new wxMenuBar();
	wxMenu *menu_new = new wxMenu;
	menu_bar->Append(menu_new, "&New...");

	wxMenu *menu_new_effects_submenu = new wxMenu;
	menu_new_effects_submenu->Append(901, "Volume control");
	menu_new_effects_submenu->Append(906, "Vibrato");
	menu_new_effects_submenu->Append(907, "Tremolo");

	menu_new->AppendSubMenu(menu_new_effects_submenu, "Effect..."); 
	wxMenu *menu_new_tones_submenu = new wxMenu;
	menu_new_tones_submenu->Append(701, "Rectangle");
	menu_new_tones_submenu->Append(702, "Additive synthesizer");

	menu_new->AppendSubMenu(menu_new_tones_submenu, "Tones...");

	wxMenu *menu_new_envelopes_submenu = new wxMenu;
	menu_new_envelopes_submenu->Append(801, "Quadratic arsd");
	menu_new_envelopes_submenu->Append(802, "Linear arsd");

	menu_new->AppendSubMenu(menu_new_envelopes_submenu, "Envelopes...");

	menu_new->Append(1000, "Instrument");

	SetMenuBar(menu_bar);

	////////////////////////////////////////////////////////////////////

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	notebook = new wxAuiNotebook(panel, wxID_ANY);

	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(250, 200);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);

	///////////////////////////////////////////////////////////////////

	//synInstrument* instrument = new synInstrument(notebook, wxID_ANY);

	notebook->AddPage(new synInstrument(notebook), "Instrument");
	
	::signal_manager.insert("Square", reinterpret_cast<Signal*>(new tones::basic::Sqr));
	::signal_manager.insert("Saw", reinterpret_cast<Signal*>(new tones::basic::Saw));
	::signal_manager.insert("Triangular", reinterpret_cast<Signal*>(new tones::basic::Tri));
	::signal_manager.insert("Sinusoidal", reinterpret_cast<Signal*>(new tones::basic::Sin));
}

void synFrame::OnVolumeControl(wxCommandEvent& event) {
	effects::VolumeControl* volume_control = new effects::VolumeControl;
	wxWindow* window = new wxWindow(notebook, wxID_ANY);
	synSlider* slider = new synSlider(window, wxID_ANY, "Volume", 0, 100, 100, reinterpret_cast<void*>(&volume_control->volume), [](void* data, int value){*reinterpret_cast<double*>(data) = value / 100.0;}, wxDefaultPosition, synSlider::Styles::FIXED);
	effect_manager.insert("Volume", dynamic_cast<WholeSampleEffect*>(volume_control));
	notebook->AddPage(window, "Volume");
}

void synFrame::OnRectangle(wxCommandEvent& event) {
	notebook->AddPage(new synRectangle(notebook), "Rectangle");
}

void synFrame::OnQuadraticARSD(wxCommandEvent& event) {
	notebook->AddPage(new synQuadraticARSD(notebook), "Quadratic ARSD");
}

void synFrame::OnVibrato(wxCommandEvent& event) {
	notebook->AddPage(new synVibrato(notebook), "Vibrato");
}

void synFrame::OnTremolo(wxCommandEvent& event) {
	notebook->AddPage(new synTremolo(notebook), "Tremolo");
}

void synFrame::OnInstrument(wxCommandEvent& event) {
	notebook->AddPage(new synInstrument(notebook), "Instrument");
}

wxBEGIN_EVENT_TABLE(synFrame, wxFrame)
	EVT_MENU(901, synFrame::OnVolumeControl)
	EVT_MENU(906, synFrame::OnVibrato)
	EVT_MENU(907, synFrame::OnTremolo)

	EVT_MENU(701, synFrame::OnRectangle)
	//EVT_MENU(702, synFrame::OnAdditiveSynthesizer)

	EVT_MENU(801, synFrame::OnQuadraticARSD)
	//EVT_MENU(802, synFrame::OnLinearARSD)

	EVT_MENU(1000, synFrame::OnInstrument)
wxEND_EVENT_TABLE();

