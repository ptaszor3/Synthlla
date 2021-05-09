#include "synFrame.hpp"
#include "synSlider.hpp"
#include "synARSD.hpp"
#include "synSignalInput.hpp"

#include <iostream>
#include <thread>

outputs::ALSAOutputStream output;
inputs::MIDIInput input;

synFrame::synFrame(std::string title, wxPoint position, wxSize size) 
:wxFrame(nullptr, wxID_ANY, title, position, size){

	instrument = new Instrument(new tones::basic::Sqr, new envelopes::arsd::Quadratic, new timers::RealTimeTimer);
	output.instrument = instrument;
	output.open();
	input.instrument = instrument;

	instrument->play(Note(440, 0_ds, 1_ds, 0.3));
	effects::VolumeControl* control = new effects::VolumeControl();
	control->volume = 0.3;
	instrument->whole_sample_effects.push_back(control);
	
	system("aconnect 20 128");

	new std::thread([]()->void{while(true)output.update();});
	new std::thread([]()->void{while(true)input.update();});

	auto arsd = new synARSD(this, wxID_ANY, &reinterpret_cast<envelopes::arsd::Quadratic*>(instrument->envelope)->arsd, wxPoint(0, 0));
	auto main_signals = new synSignalInput<Signal>(this, wxID_ANY, reinterpret_cast<Signal**>(&instrument->tone), wxPoint(0, 400), wxSize(300, 30));
	main_signals->add_signal("Square", instrument->tone);
	main_signals->add_signal("Sinusoidal", new tones::basic::Sin);
	main_signals->add_signal("Saw", new tones::basic::Saw);
	main_signals->add_signal("Triangular", new tones::basic::Tri);

	wxMenu menu;
	menu.Append(1, "Something");
	menu.Append(2, "Something else");
}
