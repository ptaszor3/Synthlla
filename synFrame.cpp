#include "synFrame.hpp"

#include "synSlider.hpp"
#include "synARSD.hpp"
#include "synMIDIInput.hpp"
#include "synEffectContext.hpp"

#include "synQuadraticARSD.hpp"
#include "synRectangle.hpp"
#include "synVibrato.hpp"
#include "synSynchronizedVibrato.hpp"
#include "synUnsynchronizedVibrato.hpp"
#include "synEffectInputsManager.hpp"
#include "synSignalInputsManager.hpp"

#include <iostream>
#include <thread>

outputs::ALSAOutputStream output;
//inputs::MIDIInput input;

synSignalInputsManager signal_manager;
synEffectInputsManager effect_manager;

synFrame::synFrame(std::string title, wxPoint position, wxSize size) 
:wxFrame(nullptr, wxID_ANY, title, position, size) {

	wxMenuBar *menu_bar = new wxMenuBar();
	wxMenu *menu_new = new wxMenu;
	menu_bar->Append(menu_new, "&New...");

	wxMenu *menu_new_effects_submenu = new wxMenu;
	menu_new_effects_submenu->Append(901, "Volume control");
	menu_new_effects_submenu->Append(902, "Synchronized vibrato");
	menu_new_effects_submenu->Append(903, "Unsynchronized vibrato");
	menu_new_effects_submenu->Append(904, "Synchronized tremolo");
	menu_new_effects_submenu->Append(905, "Unsynchronized tremolo");
	menu_new_effects_submenu->Append(906, "Vibrato");

	menu_new->AppendSubMenu(menu_new_effects_submenu, "Effect...");

	wxMenu *menu_new_tones_submenu = new wxMenu;
	menu_new_tones_submenu->Append(701, "Rectangle");
	menu_new_tones_submenu->Append(702, "Additive synthesizer");

	menu_new->AppendSubMenu(menu_new_tones_submenu, "Tones...");

	wxMenu *menu_new_envelopes_submenu = new wxMenu;
	menu_new_envelopes_submenu->Append(801, "Quadratic arsd");
	menu_new_envelopes_submenu->Append(802, "Linear arsd");

	menu_new->AppendSubMenu(menu_new_envelopes_submenu, "Envelopes...");

	SetMenuBar(menu_bar);

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	notebook = new wxAuiNotebook(panel, wxID_ANY);

	wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(250, 200);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);

	instrument = new Instrument(new tones::basic::Sqr, new envelopes::arsd::Quadratic, new timers::RealTimeTimer);
	output.instrument = instrument;
	output.open();
	//input.instrument = instrument;

	instrument->play(Note(440, 0_ds, 1_ds, 0.3));
	effects::VolumeControl* control = new effects::VolumeControl();
	control->volume = 0.3;
	instrument->whole_sample_effects.push_back(control);
	
	notebook->AddPage(new synMIDIInput(notebook, wxID_ANY, instrument), "Instrument");

	synEffectContext<SingleSampleEffect>* context = new synEffectContext(notebook, wxID_ANY, &(instrument->single_sample_effects), "Single sample effects");
	context->add_effect("vibrato", new effects::SynchronizedVibrato(new tones::basic::Sin, 100, 0.0000001_ds));
	context->add_effect("vibrato 1", new effects::SynchronizedVibrato(new tones::basic::Sin, 100, 0.0000001_ds));
	context->add_effect("vibrato 2", new effects::SynchronizedVibrato(new tones::basic::Sin, 100, 0.0000001_ds));
	context->add_effect("vibrato 3", new effects::SynchronizedVibrato(new tones::basic::Sin, 100, 0.0000001_ds));
	context->add_effect("vibrato 4", new effects::SynchronizedVibrato(new tones::basic::Sin, 100, 0.0000001_ds));

	notebook->AddPage(context, "Bududud");

	new std::thread([]()->void{while(true)output.update();});
	//new std::thread([]()->void{while(true)input.update();});

	notebook->AddPage(new synARSD(this, wxID_ANY, &reinterpret_cast<envelopes::arsd::Quadratic*>(instrument->envelope)->arsd, wxPoint(0, 0)), _("ARSD"));
	
	::signal_manager.insert("Square", reinterpret_cast<Signal*>(instrument->tone));
	::signal_manager.insert("Saw", reinterpret_cast<Signal*>(new tones::basic::Saw));
	::signal_manager.insert("Triangular", reinterpret_cast<Signal*>(new tones::basic::Tri));
	::signal_manager.insert("Sinusoidal", reinterpret_cast<Signal*>(new tones::basic::Sin));

	auto main_signals = ::signal_manager.get_new_tone_input(this, wxID_ANY, reinterpret_cast<Signal**>(&instrument->tone), "Tone", wxPoint(0, 400), wxSize(300, 30));
	//auto main_effect = ::effect_manager.get_new_single_sample_input(this, wxID_ANY, instrument, wxPoint(0, 430), wxSize(300, 30));
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

void synFrame::OnSynchronizedVibrato(wxCommandEvent& event) {
	notebook->AddPage(new synSynchronizedVibrato(notebook), "Synchronized vibrato");
}

void synFrame::OnUnsynchronizedVibrato(wxCommandEvent& event) {
	notebook->AddPage(new synUnsynchronizedVibrato(notebook), "Unsynchronized vibrato");
}

void synFrame::OnQuadraticARSD(wxCommandEvent& event) {
	notebook->AddPage(new synQuadraticARSD(notebook), "Quadratic ARSD");
}

void synFrame::OnVibrato(wxCommandEvent& event) {
	notebook->AddPage(new synVibrato(notebook), "Vibrato");
}

wxBEGIN_EVENT_TABLE(synFrame, wxFrame)
	EVT_MENU(901, synFrame::OnVolumeControl)
	EVT_MENU(902, synFrame::OnSynchronizedVibrato)
	EVT_MENU(903, synFrame::OnUnsynchronizedVibrato)
	//EVT_MENU(904, synFrame::OnSynchronizedTremolo)
	//EVT_MENU(905, synFrame::OnUnsynchronizedTremolo)
	EVT_MENU(906, synFrame::OnVibrato)

	EVT_MENU(701, synFrame::OnRectangle)
	//EVT_MENU(702, synFrame::OnAdditiveSynthesizer)

	EVT_MENU(801, synFrame::OnQuadraticARSD)
	//EVT_MENU(802, synFrame::OnLinearARSD)
wxEND_EVENT_TABLE();

