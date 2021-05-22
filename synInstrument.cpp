#include "synInstrument.hpp"
#include "synSignalInputsManager.hpp"

#include <thread>

extern synSignalInputsManager signal_manager;

synInstrument::synInstrument(wxWindow* parent, wxWindowID id, wxPoint position, wxSize size)
:wxWindow(parent, id, position, size) {
	tone = signal_manager.get_default_tone();
	envelope = signal_manager.get_default_envelope();
	timer = new timers::RealTimeTimer();

	tone_input = signal_manager.get_new_tone_input(this, wxID_ANY, &tone, "Tone:", {0, 0});
	envelope_input = signal_manager.get_new_envelope_input(this, wxID_ANY, &envelope, "Envelope:", {0, 75});
	input_input = new synMIDIInput(this, wxID_ANY, this, {0, 150});

	single_sample_context = new synEffectContext<SingleSampleEffect>(this, wxID_ANY, &(this->single_sample_effects), "Single sample effects", {230, 0}, {100, 500});
	whole_sample_context = new synEffectContext<WholeSampleEffect>(this, wxID_ANY, &(this->whole_sample_effects), "Whole sample effects", {465, 0}, {100, 500});

	output = new outputs::ALSAOutputStream(this);
	output->open();
	output->start();
}

synInstrument::~synInstrument() {
	delete output;
}
